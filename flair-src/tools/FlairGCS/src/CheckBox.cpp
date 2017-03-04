// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "CheckBox.h"
#include "Layout.h"
#include <QCheckBox>
#include <QFormLayout>

CheckBox::CheckBox(Layout *parent, int row, int col, QString name, bool value)
    : FormLayout(parent, row, col, name, "CheckBox") {
  checkbox = new QCheckBox();
  checkbox->setChecked(value);

  checkbox_value = value;

  object_layout->addRow(name, checkbox);

  connect(checkbox, SIGNAL(toggled(bool)), this, SLOT(valuechanged(bool)));

  if (checkbox_value == true) {
    SetValue("1");
  } else {
    SetValue("0");
  }
}

CheckBox::~CheckBox() { delete checkbox; }

void CheckBox::SetUptodate(void) {
  ui_to_var();
  ui_to_xml();
  visible_widget->setPalette(black_pal);
}

void CheckBox::ui_to_var(void) { checkbox_value = checkbox->isChecked(); }

void CheckBox::ui_to_xml(void) {
  if (checkbox->isChecked() == true) {
    SetValue("1");
  } else {
    SetValue("0");
  }
}

void CheckBox::Reset(void) { checkbox->setChecked(checkbox_value); }

void CheckBox::LoadEvent(QDomElement dom) {
  if (checkbox->isEnabled() == true) {
    if (dom.attribute("value") == QString("1")) {
      checkbox->setChecked(true);
    } else {
      checkbox->setChecked(false);
    }
  }
}

void CheckBox::valuechanged(bool value) {
  if (value != checkbox_value) {
    visible_widget->setPalette(red_pal);
  } else {
    visible_widget->setPalette(black_pal);
  }
}
