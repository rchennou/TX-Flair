// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#ifndef GRIDLAYOUT_H
#define GRIDLAYOUT_H

#include "Layout.h"

class GridLayout : public Layout {

public:
  GridLayout(Layout *parent, int row, int col, QString name);
  ~GridLayout();

private:
  QWidget *widget;
};

#endif // GRIDLAYOUT_H
