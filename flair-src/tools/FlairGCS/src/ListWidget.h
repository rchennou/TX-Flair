// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ListWidget.h
 * \brief Class displaying a QListWidget on the ground station
 * \author Thomas Fuhrmann, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2016/07/26
 * \version 1.0
 */
#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include "FormLayout.h"

class QListWidget;
class Layout;
class QStringList;
class QListWidgetItem;
class QPalette;
class QStringList;

/*! \class ListWidget
 *
 * \brief Class displaying a QListWidget on the ground station
 *
 */
class ListWidget : public FormLayout {
  Q_OBJECT

public:
  /**
   * \brief      Default constructor
   *
   * \param      parent  The parent widget
   * \param[in]  row     The row where to position the widget
   * \param[in]  col     The col where to position the widget
   * \param[in]  name    The name of the widget
   */
  ListWidget(Layout *parent, int row, int col, QString name);
  /**
   * \brief      Constructor with a list of default items
   *
   * \param      parent  The parent widget
   * \param[in]  row     The row where to position the widget
   * \param[in]  col     The col where to position the widget
   * \param[in]  name    The name of the widget
   * \param      items   List of items to display at creation
   */
  ListWidget(Layout *parent, int row, int col, QString name,
             QStringList &items);
  /**
   * \brief      Destructor
   */
  ~ListWidget();

private:
  /**
   * \brief      Check if the widget is up to date.
   *
   * \return     True if uptodate, False otherwise.
   */
  bool IsUptodate(void);
  /**
   * \brief      Sets the isUpToDate internal flag.
   */
  void SetUptodate(void);
  /**
   * \brief      Handler to process a new xml file.
   *
   * \param[in]  dom   The dom containing the xml file.
   */
  void XmlEvent(QDomElement dom);
  /**
   * \brief      Reset the widget, load the internal parameters.
   */

  void Reset(void);
  /**
   * \brief      Handler to process the loading of the internal xml file.
   *
   * \param[in]  dom   The dom containing the xml file.
   */
  void LoadEvent(QDomElement dom);
  /**
   * \brief      Save the user interface variables state in the internal members.
   */
  void ui_to_var(void);
  /**
   * \brief      Save the user interface variables state in the internal xml file.
   */
  void ui_to_xml(void);
  /**
   * \brief      Removes the row_to_del element from the internal xml file.
   * 
   * As the order of the elements is important, all the elements after the one
   * deleted are shifted to occupy the blank space.
   *
   * \param[in]  row_to_del  The row of the element to delete.
   */
  void RemoveItemFromXml(int row_to_del);
  /**
   * Pointer to the managed QListWidget widget.
   */
  QListWidget *listwidget;
  /**
   * Store the list of all the items, in order to use the Reset function.
   */
  QStringList *internalItemsList;
  /**
   * The row of the currently selected item.
   */
  int currentItemRow;
  /**
   * Flag to know if the widget is up to date.
   */
  bool isUpToDate;
  /**
   * Redefined color palette.
   * The highlight item's text appears in red.
   */
  QPalette palListRed;
  /**
   * Redefined color palette.
   * The highlight item's text appears in white (default).
   */
  QPalette palListDefault;

private slots:
  /**
   * \brief      Handle the change of the selected item.
   * 
   * When the selected item has changed, the text of the newly selected item appears in red,
   * to notify the user to apply the modification.
   *
   * \param[in]  current_row  The row of the currently selected item.
   */
  void SelectedItemChanged(int current_row);
};

#endif // LISTWIDGET_H
