// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "SpinBox.h"
#include <QFormLayout>
#include "Layout.h"
#include <QSpinBox>

SpinBox::SpinBox(Layout *parent, int row, int col, QString name, QString suffix,
                 int value, int min, int max, int step)
    : FormLayout(parent, row, col, name, "SpinBox") {
  spinbox = new QSpinBox();

  spinbox->setRange(min, max);
  spinbox->setSingleStep(step);
  spinbox->setValue(value);
  spinbox->setSuffix(suffix);
  spinbox_value = value;

  object_layout->addRow(name, spinbox);

  connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(valuechanged(int)));

  SetValue(QString::number(spinbox_value));
}

SpinBox::~SpinBox() { delete spinbox; }

void SpinBox::SetUptodate(void) {
  ui_to_var();
  ui_to_xml();
  visible_widget->setPalette(black_pal);
}

void SpinBox::ui_to_var(void) { spinbox_value = spinbox->value(); }

void SpinBox::ui_to_xml(void) { SetValue(QString::number(spinbox->value())); }

void SpinBox::Reset(void) { spinbox->setValue(spinbox_value); }

void SpinBox::LoadEvent(QDomElement dom) {
  if (spinbox->isEnabled() == true) {
    spinbox->setValue((dom.attribute("value")).toInt());
  }
}

void SpinBox::valuechanged(int value) {
  if (value != spinbox_value) {
    visible_widget->setPalette(red_pal);
  } else {
    visible_widget->setPalette(black_pal);
  }
}
