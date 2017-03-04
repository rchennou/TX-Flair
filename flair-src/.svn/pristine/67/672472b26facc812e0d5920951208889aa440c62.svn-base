#include <QApplication>
#include <QCleanlooksStyle>
#include <QLocale>

#include <stdio.h>
#include "unexported/compile_info.h"
#include "file_ui.h"
#include <QFileDialog>

int main(int argc, char *argv[]) {
  compile_info("Dbt2Csv");

  QLocale::setDefault(QLocale::C);
  QApplication app(argc, argv);
  app.setStyle(new QCleanlooksStyle);

  file_ui *files = new file_ui();
  files->connect(files, SIGNAL(finished()), &app, SLOT(quit()));

  QString path = QFileDialog::getExistingDirectory(new QWidget(),
                                                   "Select a directory", 0, 0);
  QDir directory(path);
  QStringList list_files = directory.entryList();

  for (int i = 0; i < list_files.size(); i++) {
    files->addFile(directory.path() + "/" + list_files.at(i));
  }

  files->endOfFiles();

  app.exec();
}
