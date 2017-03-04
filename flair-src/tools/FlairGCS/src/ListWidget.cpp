// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "ListWidget.h"
#include "Layout.h"
#include <QListWidget>
#include <QFormLayout>
#include <QLabel>
#include <QListWidgetItem>
#include <QPalette>
#include <QStringList>
#include <sstream>

//to remove, for tests only
#include <iostream>

ListWidget::ListWidget(Layout *parent, int row, int col, QString name)
    : currentItemRow(-1), isUpToDate(true),
      FormLayout(parent, row, col, name, "ListWidget") {
  listwidget = new QListWidget();
  if (internalItemsList == NULL) {
    internalItemsList = new QStringList();
  }
  // construct the object in 2 times, to have the label above the list
  object_layout->addRow(new QLabel(name));
  object_layout->addRow(listwidget);
  // modify the color palette to have the selected item text in red
  palListRed.setColor(QPalette::HighlightedText, QColor(255, 0, 0));
  palListDefault.setColor(QPalette::HighlightedText, QColor(255, 255, 255));
  connect(listwidget, SIGNAL(currentRowChanged(int)), this,
          SLOT(SelectedItemChanged(int)));
  // to avoid duplicates when adding items
  SetIsExpandable(true);
}

ListWidget::ListWidget(Layout *parent, int row, int col, QString name,
                       QStringList &items)
    : ListWidget(parent, row, col, name) {
  if (!items.isEmpty()) {
    listwidget->addItems(items);
    internalItemsList = new QStringList(items);
  }

}

ListWidget::~ListWidget() {
  if (listwidget) {
    delete listwidget;
  }
}

void ListWidget::XmlEvent(QDomElement dom) {
  isUpToDate = false;
  if (dom.attribute("item") != "") {
    QString item = dom.attribute("item");
    QListWidgetItem *widget_item = new QListWidgetItem(item);
    // new item, so the text is red
    widget_item->setForeground(Qt::red);
    listwidget->addItem(widget_item);
  }
  if (dom.attribute("delete") != "") {
    int row_to_del = dom.attribute("delete").toInt();
    RemoveItemFromXml(row_to_del);
    QListWidgetItem *item_to_del = listwidget->takeItem(row_to_del);
    if (item_to_del) {
      delete item_to_del;
    }
  }
}

void ListWidget::SetUptodate(void) {
  ui_to_var();
  ui_to_xml();
  listwidget->setPalette(palListDefault);
  isUpToDate = true;
}

void ListWidget::ui_to_var(void) {
  currentItemRow = listwidget->currentRow();
  internalItemsList->clear();
  for (int count = 0; count < listwidget->count(); count++) {
    internalItemsList->append(listwidget->item(count)->text());
  }
}

void ListWidget::ui_to_xml(void) {
  SetValue(QString::number(listwidget->currentRow()));
  // add the list of items
  for (int count = 0; count < listwidget->count(); count++) {
    std::string item;
    std::ostringstream item_prop;
    item_prop << "item" << count; 
    SetAttribute(QString::fromStdString(item_prop.str()),
                 listwidget->item(count)->text());
    listwidget->item(count)->setForeground(Qt::black);
  }
}

void ListWidget::Reset(void) {
  if (currentItemRow != -1) {
    listwidget->setCurrentRow(currentItemRow);
  }
  listwidget->clear();
  listwidget->addItems(*internalItemsList);
}

void ListWidget::LoadEvent(QDomElement dom) {
  //function not tested
  std::cout << "FlairGCS LoadEvent" << std::endl;
  if (listwidget->isEnabled() == true) {
    std::cout << "FlairGCS LoadEvent loading" << std::endl;
    listwidget->clear();
    QStringList items;
    int count = 0;
    while (dom.hasAttribute("item" + QString::number(count))) {
      std::cout << "FlairGCS LoadEvent boucle" << std::endl;
      listwidget->addItem(dom.attribute("item" + QString::number(count)));
      count++;
    }
  }
}

void ListWidget::SelectedItemChanged(int current_row) {
  if (current_row != currentItemRow) {
    isUpToDate = false;
    listwidget->setPalette(palListRed);
  } else {
    listwidget->setPalette(palListDefault);
  }
}

bool ListWidget::IsUptodate(void) { return isUpToDate; }

void ListWidget::RemoveItemFromXml(int row_to_del) {
  // Shift the elements in the XML file to have the one to delete at the end
  std::ostringstream item_prop;
  for (int count = row_to_del; count < listwidget->count() - 1; count++) {
    item_prop << "item" << count;
    SetAttribute(QString::fromStdString(item_prop.str()),
                 listwidget->item(count + 1)->text());
    // Clear the value of the stringstream
    item_prop.str(std::string());  
  }
  // Delete the last element from the XML file
  item_prop << "item" << (listwidget->count() - 1);
  RemoveAttribute(QString::fromStdString(item_prop.str()));
}
