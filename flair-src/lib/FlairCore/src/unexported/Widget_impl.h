// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file Widget_impl.h
 * \brief Classe representant un Widget
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2012/05/02
 * \version 4.0
 */

#ifndef WIDGET_IMPL_H
#define WIDGET_IMPL_H

#include <libxml/xpath.h>
#include <io_data.h>

namespace flair {
namespace gui {
class Widget;
}
}

/*! \class Widget_impl
* \brief Classe representant un Widget
*
*  C'est une classe de base. Tout comme l'Object elle permet de gérer les liens
*de parenté
*  et de détruire automatiquement les enfants. Elle permet en plus de gérer une
*communication
*  avec la station sol, et donc d'y afficher un QWidget. \n
*  La comunication avec la station sol se fait par l'échange de fichiers xml.
*Les propriétés xml du Widget sont
*  modifiables par les fonctions appropriées. \n
*  Un fichier xml de réglages par défaut du Widget est utilisé s'il a été
*spécifié à la construction du FrameworkManager.
*/
class Widget_impl {
  friend class flair::core::FrameworkManager;
  friend class FrameworkManager_impl;

public:
  /*!
  * \brief Constructeur
  *
  * Construit un Widget, qui est automatiquement enfant du parent. Le fichier
  *xml
  * spécifié au constructeur du FrameworkManager est utilisé pour les réglages
  *par
  * défaut. \n
  * Sauf pour le FrameworkManager, ce constructeur doit être apellé depuis une
  *tache temps réel
  * lorsque l'on utilise la librairie framework_rt.
  *
  * \param parent parent
  * \param name nom
  * \param type type
  */
  Widget_impl(flair::gui::Widget *self, const flair::gui::Widget *parent,
              std::string name, std::string type);

  /*!
  * \brief Déstructeur
  *
  * Détruit automatiquement les enfants.
  * La destruction implique la destruction du QWidget associé sur la station
  *sol.\n
  * Sauf pour le FrameworkManager, ce déstructeur doit être apellé depuis une
  *tache temps réel
  * lorsque l'on utilise la librairie framework_rt.
  *
  */
  ~Widget_impl();

  /*!
  * \brief Activer
  *
  * Active le QWidget associé sur la station sol. \n
  * Un QWdiget désactivé apparait grisé et n'est pas modifiable.
  *
  * \param status
  */
  void setEnabled(bool status);

  /*!
  * \brief Envoi le xml
  *
  * Envoi le xml à la station sol pour prendre en compte les changements.
  */
  void SendXml(void);

  xmlNodePtr file_node;
  xmlNodePtr send_node;
  bool isenabled;

private:
  flair::gui::Widget *self;

  std::vector<flair::gui::Widget *> childs;

  void AddChild(const flair::gui::Widget *child);
  void RemoveChild(const flair::gui::Widget *child);

  /*!
 * \brief Efface les proriétés xml
 *
 *  Permet d'effacer toutes les propriétés XML fixées par SetVolatileXmlProp.
 *  A utliser lorsque l'on a plus besoin d'utiliser ces propriétés. Utile
 * pour réduire la taille des fichiers XML écangés avec la station sol.
 */
  void ClearXmlProps(void);

  // xml
  void ProcessXML(xmlNode *node);
  xmlDocPtr CopyDoc(void);
  static xmlNodePtr GetNodeByProp(xmlNodePtr doc, xmlChar *type, xmlChar *prop,
                                  xmlChar *value);
  void printSendNode();
  xmlDocPtr send_doc;
};

#endif // WIDGET_IMPL_H
