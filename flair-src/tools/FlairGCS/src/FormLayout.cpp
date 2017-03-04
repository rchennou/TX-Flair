// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "FormLayout.h"
#include "Layout.h"
#include <QWidget>
#include <QFormLayout>
#include <QEvent>

FormLayout::FormLayout(Layout *parent, int row, int col, QString name,
                       QString type)
    : XmlWidget(name, type, parent) {
  visible_widget = new QWidget();

  // create a grid to put label and object
  visible_widget->setObjectName(name);

  parent->addWidget(visible_widget, row, col);
  object_layout = new QFormLayout(visible_widget);
  object_layout->setHorizontalSpacing(2);
  object_layout->setVerticalSpacing(2);
  object_layout->setContentsMargins(2, 2, 2, 2);

  visible_widget->installEventFilter(this);
}

FormLayout::~FormLayout() {}

bool FormLayout::IsUptodate(void) {
  // si le widget n'est pas enabled, sa palette est differente de rouge (greyed)
  // donc on renvoit true
  // permet de ne pas envoyer les modifs d'un widget disabled
  // if(label->palette()==red_pal) return false;
  if (visible_widget->palette() == red_pal)
    return false;
  return true;
}

bool FormLayout::eventFilter(QObject *o, QEvent *e) {
  if (o == visible_widget) {
    switch (e->type()) {
    case QEvent::EnabledChange: {
      QPalette palette = visible_widget->palette();
      QPalette result;

      if (palette == red_pal)
        result = red_pal_greyed;
      if (palette == red_pal_greyed)
        result = red_pal;
      if (palette == black_pal)
        result = black_pal_greyed;
      if (palette == black_pal_greyed)
        result = black_pal;

      visible_widget->setPalette(result);
    }

    default:
      break;
    }
  }
  return QObject::eventFilter(o, e);
}
