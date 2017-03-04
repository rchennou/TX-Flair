// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef FILE_UI_H
#define FILE_UI_H

#include <QObject>

class QStringList;
class QDialog;
class QTextEdit;
class QPushButton;
class QComboBox;
class QCloseEvent;

class file_ui : public QObject {
  Q_OBJECT

public:
  file_ui();
  ~file_ui();
  void log(QString text);
  void addFile(QString file_path);
  void endOfFiles(void);

private:
  QDialog *dialog;
  QStringList *file_names;
  QTextEdit *log_text, *input_text;
  QPushButton *ok_button;
  QComboBox *csv_combo;
  void save_comment(void);
  void save_csv(void);
  void save_txt(void);
  void dbt2csv(QString file_path);
  bool is_greater(qint64 ref_us, qint64 csv_us, int ref_ns, int csv_ns);
  void closeEvent(QCloseEvent *e);
  bool input_cleared;

private slots:
  void save(void);
  void clearInputText(void);

signals:
  void showDialog(void);
  void appendToLog(QString);
  void finished();
};

#endif // FILE_UI_H
