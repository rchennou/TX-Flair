//  created:    2013/06/26
//  filename:   Sinus.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    class generating a sinus signal
//
//
/*********************************************************************/

#ifndef SINUS_H
#define SINUS_H

// necessary includes, as IODevice and Thread are bases of our class
#include <IODevice.h>
#include <Thread.h>

// forward declaration for other classes
namespace flair {
namespace core {
class FrameworkManager;
class cvmatrix;
}
namespace gui {
class Tab;
class TabWidget;
class GridLayout;
class DoubleSpinBox;
class SpinBox;
class DataPlot1D;
}
}

// sinus is a class generating a sinus signal
// in this example, it emulates a sensonr, so we extend the namespace sensor
// it derives frome
// IODevice: as it has an ouput
// Thread: is it a thread
namespace flair {
namespace sensor {
class Sinus : public core::IODevice, public core::Thread {
public:
  /*!
  * \brief Constructor
  *
  * Builds a sinus generator
  *
  * \param parent the FrameworkManager to use
  * \param name object name
  * \param priority Thread priority, 50 by default (1:mini, 99:maxi)
  */
  Sinus(const core::FrameworkManager *parent, std::string name,
        int priority = 50);

  /*!
  * \brief Destructor
  */
  ~Sinus();

  /*!
  * \brief Output matrix
  *
  * allows to access output matrix, to get signal value or to put it in a graph.
  *\n
  *
  * \return un pointeur vers la matrice de sortie
  */
  core::cvmatrix *GetMatrix(void) const;

  /*!
  * \brief Value
  *
  * this method is equivalent to GetMatrix()->Value(0,0)
  *
  * \return actual signal value
  */
  float GetValue(void) const;

  /*!
  * \brief Use defautl plot
  *
  * this method put a graph in a specific tab
  *
  */
  void UseDefaultPlot(void);

  /*!
  * \brief SetupLayout
  *
  * this method allows to add other widgets in the sinus tab.
  *
  * \return the GridLayout
  */
  gui::GridLayout *GetSetupLayout(void) const;

  /*!
  * \brief Plot
  *
  * this method allows to add other curves in the graph
  *
  * \return the DataPlot1D
  */
  gui::DataPlot1D *GetPlot(void) const;

private:
  // UpdateFrom method from base class IODevice
  // sinus is like a sensor, so it does not have input; we define an empty
  // method
  void UpdateFrom(const core::io_data *data){};
  void Run(void);

  core::cvmatrix *output;
  gui::Tab *mainTab;
  gui::TabWidget *tabWidget;
  gui::DataPlot1D *plot;
  gui::DoubleSpinBox *frequency, *amplitude, *offset;
  gui::SpinBox *period;
  gui::GridLayout *setupLayout;
};
} // end namespace sensor
} // end namespace flair
#endif // SINUS_H
