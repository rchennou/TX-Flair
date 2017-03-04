// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2016/07/26
//  filename:   ListWidget.cpp
//
//  author:     Thomas Fuhrmann
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    Class displaying a QListWidget on the ground station
//
//
/*********************************************************************/
#include "ListWidget.h"
#include "Layout.h"
#include "LayoutPosition.h"

#include <sstream>

using std::string;

namespace flair {
namespace gui {

ListWidget::ListWidget(const LayoutPosition *position, string name)
    : Widget(position->getLayout(), name, string("ListWidget")),
    selectedItemRow(-1), selectedItemChanged(false) {
  // load the items in the xml file and send them to the ground station
  size_t count = 0;
  while (1) {
    string item;
    std::ostringstream item_prop;
    item_prop << "item" << count;
    if (GetPersistentXmlProp(item_prop.str(), item)) {
      SetVolatileXmlProp(item_prop.str(), item);
      items.push_back(item);
    } else {
      break;
    }
    count++;
  }
  SetVolatileXmlProp("row", position->Row());
  SetVolatileXmlProp("col", position->Col());
  delete position;
  SendXml();
}

ListWidget::~ListWidget() { core::Object::ObjectName(); }

void ListWidget::AddItem(string name) {
  items.push_back(name);
  SetVolatileXmlProp("item", name);
  SendXml();
}

void ListWidget::RemoveItem(void) {
  if (selectedItemChanged) {
    // Delete the the last item, the xml file will automatically be updated by the GUI
    // TODO diff when the apply all xml file is received to avoid clear here
    std::ostringstream item_prop;
    item_prop << "item" << (items.size() - 1);
    UnsetPersistentXmlProp(item_prop.str());
    // Delete the item from the internal list and ask the GUI to delete it
    selectedItemChanged = false;
    items.erase(items.cbegin() + selectedItemRow);
    SetVolatileXmlProp("delete", selectedItemRow);
    SendXml();
  }
}

void ListWidget::XmlEvent(void) {
  if (GetPersistentXmlProp("value", selectedItemRow)) {
    selectedItemChanged = true;
  }
}

const std::vector<std::string> &ListWidget::GetItemList() const {
  return items;
}

} // end namespace gui
} // end namespace flair
