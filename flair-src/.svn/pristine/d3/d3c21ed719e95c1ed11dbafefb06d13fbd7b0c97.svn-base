// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "DoubleSpinBox.h"
#include "Layout.h"
#include <QLineEdit>
#include <QMenu>
#include <QContextMenuEvent>
#include <QDoubleSpinBox>
#include <QFormLayout>

DoubleSpinBox::DoubleSpinBox(Layout *parent, int row, int col, QString name,
                             QString suffix, QString value, float min,
                             float max, float step, int decimals)
    : FormLayout(parent, row, col, name, "DoubleSpinBox") {
  doublespinbox = new QDoubleSpinBox();

  doublespinbox->setRange(min, max);
  doublespinbox->setSingleStep(step);
  doublespinbox->setDecimals(decimals);
  if (suffix != "")
    doublespinbox->setSuffix(suffix);
  adjust_decimals(value);
  doublespinbox->setValue(value.toDouble());
  doublespinbox_value = doublespinbox->cleanText();

  // event filter for qdoublespinbox and its child (qlinedit and incremnt
  // qbuttons)
  doublespinbox->installEventFilter(this);
  QObjectList o_list = doublespinbox->children();
  for (int i = 0; i < o_list.length(); i++) {
    QLineEdit *cast = qobject_cast<QLineEdit *>(o_list[i]);
    if (cast)
      cast->installEventFilter(this);
  }

  object_layout->addRow(name, doublespinbox);

  connect(doublespinbox, SIGNAL(valueChanged(const QString &)), this,
          SLOT(valuechanged(const QString &)));

  SetValue(value);
}

DoubleSpinBox::~DoubleSpinBox() { delete doublespinbox; }

void DoubleSpinBox::adjust_decimals(QString value) {
  // auto adjust decimals
  QLocale locale;
  value.remove(locale.groupSeparator());

  QStringList parts = value.split(locale.decimalPoint());
  if (parts.count() == 2) {
    doublespinbox->setDecimals(parts[1].size());
  }
}

bool DoubleSpinBox::eventFilter(QObject *object, QEvent *event) {
  if (object == doublespinbox && event->type() == QEvent::MouseButtonPress) {
    if (((QMouseEvent *)event)->button() == Qt::RightButton) {
      QMenu *menu = new QMenu("menu", doublespinbox);
      QAction *a, *b, *c, *z;

      a = menu->addAction("add decimal");
      b = menu->addAction("remove decimal");

      if (doublespinbox->decimals() == 0)
        b->setEnabled(false);
      z = menu->exec(((QMouseEvent *)event)->globalPos());

      if (z == a)
        doublespinbox->setDecimals(doublespinbox->decimals() + 1);
      if (z == b)
        doublespinbox->setDecimals(doublespinbox->decimals() - 1);
      delete menu;
      return true;
    }
  }

  return object->eventFilter(object, event);
}

void DoubleSpinBox::SetUptodate(void) {
  ui_to_var();
  ui_to_xml();
  visible_widget->setPalette(black_pal);
}

void DoubleSpinBox::ui_to_var(void) {
  doublespinbox_value = doublespinbox->cleanText();
}

void DoubleSpinBox::ui_to_xml(void) { SetValue(doublespinbox->cleanText()); }

void DoubleSpinBox::Reset(void) {
  // le setvalue fait un arrondi pour l'affichage, la variable n'est donc plus
  // egale
  // on reprend la valeur de la boite et on force la couleur a noir
  adjust_decimals(doublespinbox_value);
  doublespinbox->setValue(doublespinbox_value.toDouble());
  doublespinbox_value = doublespinbox->cleanText();
  visible_widget->setPalette(black_pal);
}

void DoubleSpinBox::LoadEvent(QDomElement dom) {
  if (doublespinbox->isEnabled() == true) {
    doublespinbox->setValue((dom.attribute("value")).toDouble());
  }
}

void DoubleSpinBox::valuechanged(const QString &value) {
  if (value != doublespinbox_value) {
    visible_widget->setPalette(red_pal);
  } else {
    visible_widget->setPalette(black_pal);
  }
}
