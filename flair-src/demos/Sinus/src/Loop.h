//  created:    2013/06/26
//  filename:   Loop.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//
//
/*********************************************************************/

#ifndef LOOP_H
#define LOOP_H

// necessary include, as Thread is a base of our class
#include <Thread.h>

// forward declaration for other classes
namespace flair {
namespace core {
class FrameworkManager;
}
namespace gui {
class PushButton;
class SpinBox;
}
namespace sensor {
class Sinus;
}
namespace filter {
class LowPassFilter;
class ButterworthLowPass;
class MeanFilter;
}
}

class Loop : public flair::core::Thread {
public:
  /*!
  * \brief Constructor
  *
  * Builds main loop
  *
  * \param parent the FrameworkManager to use
  * \param name object name
  * \param priority Thread priority, 51 by default (1:mini, 99:maxi)
  */
  Loop(flair::core::FrameworkManager *parent, std::string name,
       int priority = 51);

  /*!
  * \brief Destructor
  */
  ~Loop();

private:
  void Run(void);

  flair::sensor::Sinus *sinus;
  flair::filter::LowPassFilter *firstLowPass;
  flair::filter::ButterworthLowPass *thirdLowPass;
  flair::filter::MeanFilter *mean, *meanOnfirstLowPass;
  flair::gui::PushButton *startLogButton, *stopLogButton, *killButton;
  flair::gui::SpinBox *period;
};

#endif // LOOP_H
