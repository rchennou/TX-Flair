// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "ComboBox.h"
#include "Layout.h"
#include <QComboBox>
#include <QFormLayout>

ComboBox::ComboBox(Layout *parent, int row, int col, QString name, int value)
    : FormLayout(parent, row, col, name, "ComboBox") {
  combobox = new QComboBox();
  combobox->setCurrentIndex(value);

  combobox_value = value;

  object_layout->addRow(name, combobox);

  connect(combobox, SIGNAL(currentIndexChanged(int)), this,
          SLOT(valuechanged(int)));

  SetValue(QString::number(combobox_value));

  // pour ne pas faire de doublons qd on ajoute des items
  SetIsExpandable(true);
}

ComboBox::~ComboBox() { delete combobox; }

void ComboBox::XmlEvent(QDomElement dom) {
  if (dom.attribute("item") != "") {
    QString item = dom.attribute("item");
    combobox->addItem(item);
    combobox->setCurrentIndex(combobox_value);
  }
}

void ComboBox::SetUptodate(void) {
  ui_to_var();
  ui_to_xml();
  visible_widget->setPalette(black_pal);
}

void ComboBox::ui_to_var(void) { combobox_value = combobox->currentIndex(); }

void ComboBox::ui_to_xml(void) {
  SetValue(QString::number(combobox->currentIndex()));
}

void ComboBox::Reset(void) { combobox->setCurrentIndex(combobox_value); }

void ComboBox::LoadEvent(QDomElement dom) {
  if (combobox->isEnabled() == true) {
    combobox->setCurrentIndex((dom.attribute("value")).toInt());
  }
}

void ComboBox::valuechanged(int value) {
  if (value != combobox_value) {
    visible_widget->setPalette(red_pal);
  } else {
    visible_widget->setPalette(black_pal);
  }
}
