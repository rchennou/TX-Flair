// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Widget.h
 * \brief Abstract class for all Framework's widget classes
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/05/02
 * \version 4.0
 */

#ifndef WIDGET_H
#define WIDGET_H

#include <Object.h>
//#include <io_data.h>
#include <libxml/xpath.h>

class Widget_impl;
class FrameworkManager_impl;

namespace flair {
namespace gui {

/*! \class Widget
*
* \brief Abstract class for all Framework's widget classes
*
* A widget is an object to display on the ground station. \n
* Communication with ground station is done through xml files; properties of
*theses files
* are modified through appropriate method. \n
* A xml file is used for default values of the Widget, if it has been specified
*in the
*  constructor of the FrameworkManager.
*/
class Widget : public core::Object {
  friend class core::FrameworkManager;
  friend class ::Widget_impl;
  friend class ::FrameworkManager_impl;

public:
  /*!
  * \brief Constructor
  *
  * Construct a Widget, the xml file specified to the FrameworkManager's
  * constructor is sued for default values. \n
  * Two Widget with same parent must have different names. If a brother Widget
  *already
  * has the same name, the name of the new one will be automatically changed. \n
  * Type must agree with predifined (hard coded) types
  * in ground station code.
  *
  * \param parent parent
  * \param name name
  * \param type type
  */
  Widget(const Widget *parent, std::string name, std::string type);

  /*!
  * \brief Destructor
  *
  */
  virtual ~Widget();

  /*!
  * \brief Set enabled
  *
  * Enable or disable the Widget on the ground station. \n
  * A disabled widget is greyed out on the ground station
  * and in unmodifiable.
  *
  * \param status
  */
  void setEnabled(bool status);

  /*!
  * \brief Is enabled?
  *
  * \return true if widget is enabled
  */
  bool isEnabled(void) const;

protected:
  /*!
  * \brief Set a persistent xml property
  *
  * The property will be saved in the configuration xml and also used to
  *configure the ground station.
  *
  * \param prop property to set and save
  * \param value value to set and save
  */
  template <typename T> void SetPersistentXmlProp(std::string prop, T value);

  /*!
  * \brief Get a persistent xml property
  *
  * Get the property from the xml file. If no corresponding property is found in
  *the xml, value remains unchanged. \n
  * Thus value can be initialized with a default value before calling this
  *method.
  *
  * \param prop property to get
  * \param value value to store the result
  * \return true if value was changed
  */
  template <typename T> bool GetPersistentXmlProp(std::string prop, T &value);

  /*!
  * \brief Set a volatile xml property
  *
  * This property should be used to configure the ground station (one time
  *init). \n
  * The property will be destroyed after calling SendXml() as it should no be
  *used anymore.
  *
  * \param prop property to set
  * \param value value to set
  * \param node if sepcified, node to set; otherwise use the node of the Widget
  */
  template <typename T>
  void SetVolatileXmlProp(std::string prop, T value, xmlNodePtr node = NULL);

  /*!
  * \brief Send xml
  *
  * Send Widget's xml to ground station. \n
  * New changes will be taken into account by ground station. \n
  * All volatile properties will be erased after calling ths method, as they
  *should not be used anymore.
  */
  void SendXml(void);

  /*!
  * \brief Xml event
  *
  * This method must be reimplemented to handle a xml event. \n
  * It is automatically called when something changed from
  * ground station. \n
  */
  virtual void XmlEvent(void){};

  /*!
   * \brief Unset a persistent xml property
   * 
   * Unset an existent property, so it won't be saved.
   *
   * \param prop property to set
   */
  void UnsetPersistentXmlProp(std::string prop);

private:
  class Widget_impl *pimpl_;
};

} // end namespace gui
} // end namespace flair

#endif // WIDGET_H
