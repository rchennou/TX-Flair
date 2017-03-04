// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "file_ui.h"
#include <stdio.h>

#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <QDir>
#include <QDate>
#include <QTextStream>
#include <QGridLayout>
#include <io_hdfile.h>
#include <QtEndian>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QDialog>
#include <QStringList>
#include <QFormLayout>

#ifndef WIN32
#include <arpa/inet.h>
#else
#include <winsock2.h>
#include <ws2tcpip.h>
#endif

using namespace std;

file_ui::file_ui() {
  dialog = new QDialog();
  dialog->setWindowTitle("log files");
  QGridLayout *main_layout = new QGridLayout(dialog);
  ok_button = new QPushButton("Ok", dialog);
  log_text = new QTextEdit(dialog);
  log_text->setReadOnly(true);
  input_text = new QTextEdit(dialog);
  input_text->setText("add your log comment here");
  input_cleared = false;

  ok_button->setEnabled(false);

  main_layout->addWidget(log_text, 0, 0);
  main_layout->addWidget(input_text, 1, 0);

  QWidget *widget = new QWidget(dialog);
  QFormLayout *formLayout = new QFormLayout(widget);
  csv_combo = new QComboBox(widget);
  formLayout->addRow(tr("save all log with following base time"), csv_combo);
  csv_combo->addItem("(no base time)");
  main_layout->addWidget(widget, 2, 0);
  main_layout->addWidget(ok_button, 3, 0);

  connect(ok_button, SIGNAL(clicked()), this, SLOT(save()),
          Qt::QueuedConnection);
  connect(this, SIGNAL(showDialog()), dialog, SLOT(show()),
          Qt::QueuedConnection);
  connect(this, SIGNAL(appendToLog(QString)), log_text, SLOT(append(QString)),
          Qt::QueuedConnection);
  connect(input_text, SIGNAL(cursorPositionChanged()), this,
          SLOT(clearInputText()), Qt::QueuedConnection);

  file_names = new QStringList();
}

file_ui::~file_ui() { delete dialog; }

void file_ui::log(QString text) { appendToLog(text); }

void file_ui::addFile(QString file_path) {
  // framework sends dbt file then txt file
  // when we receive txt, we have both files
  // and we can convert it to .csv
  if (file_path.endsWith(".dbt") == true) {
    QString name =
        file_path.section('/', -1); // remove path for displaying on combobox
    csv_combo->addItem(name.replace(QString(".dbt"), QString(".csv")));
    file_names->append(file_path.replace(QString(".dbt"), QString(".csv")));
  }

  if (file_path.endsWith(".txt") == true) {
    dbt2csv(file_path.replace(QString(".txt"), QString(".dbt")));
  }

  if (file_names->size() == 1) {
    input_cleared = false;
    showDialog();
  }
}

void file_ui::endOfFiles(void) {
  ok_button->setEnabled(true);

  qint64 max_file_size = 0;
  for (int i = 0; i < file_names->count(); i++) {
    QFileInfo info(file_names->at(i));
    if (info.size() > max_file_size) {
      max_file_size = info.size();
      csv_combo->setCurrentIndex(i +
                                 1); // first item of combobox is already taken
    }
  }
}

void file_ui::dbt2csv(QString file_path) {
  hdfile_t *dbtFile = NULL;
  char *data;
  QStringList data_type;

  QString filename =
      file_path.section('/', -1); // remove path for displaying on logs
  appendToLog(QString("converting %1 to csv").arg(filename));

  // open csv file
  QString csv_filename = file_path;
  csv_filename.replace(QString(".dbt"), QString(".csv"));
  QFile csv_file(csv_filename);

  if (!csv_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    appendToLog("      error opening csv file!");
    return;
  }
  QTextStream out(&csv_file);

  // open txt file
  QString txt_filename = file_path;
  txt_filename.replace(QString(".dbt"), QString(".txt"));
  QFile txt_file(txt_filename);

  if (!txt_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    appendToLog("      error opening txt file!");
    return;
  }

  // read txt file
  QTextStream txt_in(&txt_file);
  txt_in.readLine(); // time us
  txt_in.readLine(); // time ns
  while (1) {
    if (txt_in.atEnd() == true)
      break;
    QString txt_line = txt_in.readLine();
    data_type.append(txt_line.section(
        "(",
        -1)); // on part de la fin pour trouver la premiere parenthese ouvrante
    // printf("type %s\n",txt_line.section("(",-1).toLocal8Bit().constData());
  }
  txt_file.close();

  dbtFile = open_hdfile(file_path.toLocal8Bit().data(), READ_MODE);

  if (!dbtFile) {
    appendToLog("      error opening dbt file!");
    return;
  }
  data = (char *)malloc(dbtFile->h.DataSize);
  if (data == NULL) {
    appendToLog("      error malloc!");
    return;
  }

  bool dataWritten = false;
  while (1) {
    road_time_t time;
    road_timerange_t tr = 0;
    int offset = 0;
    QTextStream csv_line;

    if (read_hdfile(dbtFile, (void *)data, &time, &tr) == 0) {
      break;
    }
    dataWritten = true;

    out << time << "," << tr;
    for (int i = 0; i < data_type.size(); i++) {
      if (data_type.at(i) == "double)") {
        double *value = (double *)(data + offset);
        offset += sizeof(double);
        out << "," << *value;
      } else if (data_type.at(i) == "float)") {
        float *value = (float *)(data + offset);
        offset += sizeof(float);
        out << "," << *value;
      } else if (data_type.at(i) == "int8_t)") {
        int8_t *value = (int8_t *)(data + offset);
        offset += sizeof(int8_t);
        out << "," << *value;
      } else if (data_type.at(i) == "uint8_t)") {
        uint8_t *value = (uint8_t *)(data + offset);
        offset += sizeof(uint8_t);
        out << "," << *value;
      } else {
        appendToLog(QString("      unhandled type: %1").arg(data_type.at(i)));
      }
    }

    out << "\n";
  }

  if (!dataWritten) {
    // empty file!
    out << "0,0"; // timr
    for (int i = 0; i < data_type.size(); i++) {
      out << ",0";
    }
    out << "\n";
  }

  csv_file.close();
  close_hdfile(dbtFile);
  if (data != NULL)
    free(data);

  appendToLog("      ok");
}

void file_ui::clearInputText(void) {
  if (input_cleared == false) {
    input_cleared = true;
    input_text->clear();
  }
}

void file_ui::save(void) {
  save_comment();
  if (csv_combo->currentIndex() != 0) {
    save_csv();
    save_txt();
  }

  log_text->clear();
  input_cleared = true; // avoid clearing it with setText
  input_text->setText("add your log comment here");
  file_names->clear();
  csv_combo->clear();
  csv_combo->addItem(QString("(no base time)"));

  dialog->setVisible(false);
  ok_button->setEnabled(false);
  emit finished();
}

void file_ui::save_comment(void) {
  QString folder_name = file_names->at(0).section('/', 0, -2);

  QString filename = folder_name + "/commentaire.txt";
  QFile file(filename);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    printf("file_ui::save_comment: erreur ouverture fichier %s\n",
           filename.toLocal8Bit().constData());
  QTextStream out(&file);

  out << input_text->toPlainText();
  file.close();
}

void file_ui::save_csv(void) {
  // global csv file
  QString folder_name = file_names->at(0).section('/', 0, -2);
  QString filename = folder_name + "/all_logs.csv";
  QFile global_file(filename);
  if (!global_file.open(QIODevice::WriteOnly | QIODevice::Text))
    printf("file_ui::save_csv: erreur ouverture fichier %s\n",
           filename.toLocal8Bit().constData());
  QTextStream out(&global_file);

  // reference csv file
  filename = file_names->at(csv_combo->currentIndex() - 1);
  QFile ref_file(filename);
  // printf("file_ui::save_csv: ref %s\n",filename.toLocal8Bit().constData());
  if (!ref_file.open(QIODevice::ReadOnly | QIODevice::Text))
    printf("file_ui::save_csv: erreur ouverture ficher %s\n",
           filename.toLocal8Bit().constData());

  // other csv files
  int j = 0;
  QFile m_file[file_names->count() - 1];
  QTextStream m_in[file_names->count() - 1];
  for (int i = 0; i < file_names->count(); i++) {
    if (i == csv_combo->currentIndex() - 1)
      continue;
    filename = file_names->at(i);
    m_file[j].setFileName(filename);
    if (!m_file[j].open(QIODevice::ReadOnly | QIODevice::Text))
      printf("file_ui::save_csv: erreur ouverture ficher %s\n",
             filename.toLocal8Bit().constData());
    m_in[j].setDevice(&m_file[j]);
    j++;
  }

  // init
  QTextStream ref_in(&ref_file);
  QString m_line[file_names->count() - 1];
  QString m_line_prev[file_names->count() - 1];
  for (int i = 0; i < file_names->count() - 1; i++) {
    m_line[i] = m_in[i].readLine();
    m_line_prev[i] = m_line[i];
  }

  // organize csv files in one file
  while (1) {
    if (ref_in.atEnd() == true)
      break;
    QString ref_line = ref_in.readLine();

    qint64 ref_us = ref_line.section(',', 0, 0).toLongLong();
    int ref_ns = ref_line.section(',', 1, 1).toInt();
    // printf("ref %lld %i\n",ref_us,ref_ns);

    for (int i = 0; i < file_names->count() - 1; i++) {
      qint64 csv_us = m_line[i].section(',', 0, 0).toLongLong();
      int csv_ns = m_line[i].section(',', 1, 1).toInt();
      // printf("m %lld %i\n",csv_us,csv_ns);

      while (is_greater(ref_us, csv_us, ref_ns, csv_ns) == true) {
        m_line_prev[i] = m_line[i];
        if (m_in[i].atEnd() == true)
          break;
        m_line[i] = m_in[i].readLine();
        csv_us = m_line[i].section(',', 0, 0).toLongLong();
        csv_ns = m_line[i].section(',', 1, 1).toInt();
        // printf("m %lld %i\n",csv_us,csv_ns);
      }
      csv_us = m_line_prev[i].section(',', 0, 0).toLongLong();
      csv_ns = m_line_prev[i].section(',', 1, 1).toInt();
      // printf("m ok %lld %i\n",csv_us,csv_ns);

      ref_line += "," + m_line_prev[i].section(',', 2);
    }

    out << ref_line << "\n";
  }

  global_file.close();
  ref_file.close();
  for (int i = 0; i < file_names->count() - 1; i++)
    m_file[i].close();
}

void file_ui::save_txt(void) {
  // global txt file
  QString folder_name = file_names->at(0).section('/', 0, -2);
  QString filename = folder_name + "/all_logs.txt";
  QFile global_file(filename);
  if (!global_file.open(QIODevice::WriteOnly | QIODevice::Text))
    printf("file_ui::save_txt: erreur ouverture ficher %s\n",
           filename.toLocal8Bit().constData());
  QTextStream out(&global_file);

  // reference txt file
  filename = file_names->at(csv_combo->currentIndex() - 1);
  filename.replace(QString(".csv"), QString(".txt"));
  QFile ref_file(filename);
  if (!ref_file.open(QIODevice::ReadOnly | QIODevice::Text))
    printf("file_ui::save_txt: erreur ouverture ficher %s\n",
           filename.toLocal8Bit().constData());

  QTextStream ref_in(&ref_file);
  QString current_line = ref_in.readLine();
  int nb_lines = 1;
  while (current_line != NULL) {
    out << current_line << "\n";
    ;
    current_line = ref_in.readLine();
    nb_lines++;
  }

  // other txt files
  for (int i = 0; i < file_names->count(); i++) {
    if (i == csv_combo->currentIndex() - 1)
      continue;
    filename = file_names->at(i);
    filename.replace(QString(".csv"), QString(".txt"));
    QFile txt_file(filename);
    if (!txt_file.open(QIODevice::ReadOnly | QIODevice::Text))
      printf("file_ui::save_txt: erreur ouverture ficher %s\n",
             filename.toLocal8Bit().constData());
    QTextStream txt_in(&txt_file);
    txt_in.readLine(); // time us
    txt_in.readLine(); // time ns
    current_line = txt_in.readLine();
    while (current_line != NULL) {
      out << nb_lines << ":" << current_line.section(':', 1) << "\n";
      ;
      current_line = txt_in.readLine();
      nb_lines++;
    }
    txt_file.close();
  }
  global_file.close();
  ref_file.close();
}

bool file_ui::is_greater(qint64 ref_us, qint64 csv_us, int ref_ns, int csv_ns) {
  if (ref_us == csv_us) {
    if (ref_ns > csv_ns) {
      return true;
    } else {
      return false;
    }
  }
  if (ref_us > csv_us) {
    return true;
  } else {
    return false;
  }
}
