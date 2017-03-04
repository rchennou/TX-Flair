// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "Vector3DSpinBox.h"
#include <QLineEdit>
#include <QMenu>
#include <QContextMenuEvent>
//#include <QGridLayout>
#include <QFormLayout>
#include <QGroupBox>
#include "Layout.h"

Vector3DSpinBox::Vector3DSpinBox(Layout *parent, int row, int col, QString name,
                                 QString value[3], float min, float max,
                                 float step, int decimals)
    : XmlWidget(name, "Vector3DSpinBox", parent) {
  for (int i = 0; i < 3; i++) {
    doublespinbox[i].setRange(min, max);
    doublespinbox[i].setSingleStep(step);
    doublespinbox[i].setDecimals(decimals);
  }

  adjust_decimals(value);

  for (int i = 0; i < 3; i++) {
    doublespinbox[i].setValue(value[i].toDouble());
    doublespinbox_value[i] = doublespinbox[i].cleanText();

    // event filter for qdoublespinbox and its child (qlinedit and incremnt
    // qbuttons)
    doublespinbox[i].installEventFilter(this);
    QObjectList o_list = doublespinbox[i].children();
    for (int j = 0; j < o_list.length(); j++) {
      QLineEdit *cast = qobject_cast<QLineEdit *>(o_list[j]);
      if (cast)
        cast->installEventFilter(this);
    }

    connect(&doublespinbox[i], SIGNAL(valueChanged(const QString &)), this,
            SLOT(valuechanged(const QString &)));
  }

  SetValues(value);

  // creation et ajout QGroupBox
  box = new QGroupBox(name);
  box->setObjectName(name);
  visible_widget = box;
  parent->addWidget(box, row, col);
  qgridlayout = new QGridLayout(new QWidget());
  box->setLayout(qgridlayout);

  AddElement("x:", 0);
  AddElement("y:", 1);
  AddElement("z:", 2);
}

Vector3DSpinBox::~Vector3DSpinBox() {}

void Vector3DSpinBox::SetValues(QString value[3]) {
  SetAttribute("value_x", value[0]);
  SetAttribute("value_y", value[1]);
  SetAttribute("value_z", value[2]);
}

void Vector3DSpinBox::AddElement(QString name, int index) {
  QWidget *widget = new QWidget();
  QFormLayout *object_layout = new QFormLayout(widget);
  object_layout->setHorizontalSpacing(2);
  object_layout->setVerticalSpacing(2);
  object_layout->setContentsMargins(2, 2, 2, 2);

  object_layout->addRow(name, &doublespinbox[index]);

  qgridlayout->addWidget(widget, index, 0);
}

void Vector3DSpinBox::adjust_decimals(QString value[3]) {
  for (int i = 0; i < 3; i++) {
    // auto adjust decimals
    QLocale locale;
    value[i].remove(locale.groupSeparator());

    QStringList parts = value[i].split(locale.decimalPoint());
    if (parts.count() == 2) {
      doublespinbox[i].setDecimals(parts[1].size());
    }
  }
}

bool Vector3DSpinBox::eventFilter(QObject *object, QEvent *event) {
  for (int i = 0; i < 3; i++) {
    if (object == &doublespinbox[i] &&
        event->type() == QEvent::MouseButtonPress) {
      if (((QMouseEvent *)event)->button() == Qt::RightButton) {
        QMenu *menu = new QMenu("menu", doublespinbox);
        QAction *a, *b, *c, *z;

        a = menu->addAction("add decimal");
        b = menu->addAction("remove decimal");

        if (doublespinbox[i].decimals() == 0)
          b->setEnabled(false);
        z = menu->exec(((QMouseEvent *)event)->globalPos());

        if (z == a)
          doublespinbox[i].setDecimals(doublespinbox[i].decimals() + 1);
        if (z == b)
          doublespinbox[i].setDecimals(doublespinbox[i].decimals() - 1);
        delete menu;
        return true;
      }
    }
  }
  return object->eventFilter(object, event);
}

void Vector3DSpinBox::SetUptodate(void) {
  ui_to_var();
  ui_to_xml();
  visible_widget->setPalette(black_pal);
}

void Vector3DSpinBox::ui_to_var(void) {
  for (int i = 0; i < 3; i++) {
    doublespinbox_value[i] = doublespinbox[i].cleanText();
  }
}

void Vector3DSpinBox::ui_to_xml(void) {
  SetAttribute("value_x", doublespinbox[0].cleanText());
  SetAttribute("value_y", doublespinbox[1].cleanText());
  SetAttribute("value_z", doublespinbox[2].cleanText());
}

void Vector3DSpinBox::Reset(void) {
  // le setvalue fait un arrondi pour l'affichage, la variable n'est donc plus
  // egale
  // on reprend la valeur de la boite et on force la couleur a noir
  adjust_decimals(doublespinbox_value);
  for (int i = 0; i < 3; i++) {
    doublespinbox[i].setValue(doublespinbox_value[i].toDouble());
    doublespinbox_value[i] = doublespinbox[i].cleanText();
  }
  visible_widget->setPalette(black_pal);
}

void Vector3DSpinBox::LoadEvent(QDomElement dom) {
  if (doublespinbox[0].isEnabled()) {
    doublespinbox[0].setValue((dom.attribute("value_x")).toDouble());
  }
  if (doublespinbox[1].isEnabled()) {
    doublespinbox[1].setValue((dom.attribute("value_y")).toDouble());
  }
  if (doublespinbox[2].isEnabled()) {
    doublespinbox[2].setValue((dom.attribute("value_z")).toDouble());
  }
}

void Vector3DSpinBox::valuechanged(const QString &value) {
  for (int i = 0; i < 3; i++) {
    if ((QDoubleSpinBox *)sender() == &doublespinbox[i] &&
        value != doublespinbox_value[i]) {
      visible_widget->setPalette(red_pal);
      return;
    }
  }
  visible_widget->setPalette(black_pal);
}

bool Vector3DSpinBox::IsUptodate(void) {
  // si le widget n'est pas enabled, sa palette est differente de rouge (greyed)
  // donc on renvoit true
  // permet de ne pas envoyer les modifs d'un widget disabled
  // if(label->palette()==red_pal) return false;
  if (visible_widget->palette() == red_pal)
    return false;
  return true;
}
