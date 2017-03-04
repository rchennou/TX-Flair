// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file ButterworthLowPass_impl.h
 * \brief Classe permettant le calcul d'un filtre passe bas de Butterworth
 * \author Guillaume Sanahuja, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2011/05/01
 * \version 4.0
 */

#ifndef BUTTERWORTHLOWPASS_H_IMPL_H
#define BUTTERWORTHLOWPASS_H_IMPL_H

#include <IODevice.h>
#include <Butterworth.h>

namespace flair {
namespace core {
class cvmatrix;
}
namespace gui {
class LayoutPosition;
class SpinBox;
class DoubleSpinBox;
}
namespace filter {
class ButterworthLowPass;
}
}

// Storage for Layout
// de-templatized for pimpl idom
// comes from iir from Bernd Porr
class LayoutStorage {
public:
  LayoutStorage(int MaxPoles) {
    this->MaxPoles = MaxPoles;
    m_pairs = (Iir::PoleZeroPair *)malloc((MaxPoles + 1) / 2 *
                                          sizeof(Iir::PoleZeroPair));
  }
  ~LayoutStorage() { free(m_pairs); }
  operator Iir::LayoutBase() { return Iir::LayoutBase(MaxPoles, m_pairs); }

private:
  Iir::PoleZeroPair *m_pairs;
  int MaxPoles;
};

// Storage for Cascade
// de-templatized for pimpl idom
// comes from iir from Bernd Porr
class CascadeStages {
public:
  CascadeStages(int MaxStages) {
    this->MaxStages = MaxStages;
    m_stages =
        (Iir::Cascade::Stage *)malloc(MaxStages * sizeof(Iir::Cascade::Stage));
    m_states =
        (Iir::DirectFormII *)malloc(MaxStages * sizeof(Iir::DirectFormII));
  }
  ~CascadeStages() {
    free(m_stages);
    free(m_states);
  }
  void reset() {
    Iir::DirectFormII *state = m_states;
    for (int i = MaxStages; --i >= 0; ++state)
      state->reset();
  }

  template <typename Sample> inline Sample filter(const Sample in) {
    double out = in;
    Iir::DirectFormII *state = m_states;
    Iir::Biquad const *stage = m_stages;
    for (int i = MaxStages; --i >= 0; ++state, ++stage)
      out = state->process1(out, *stage);
    return static_cast<Sample>(out);
  }

  Iir::Cascade::Storage getCascadeStorage() {
    return Iir::Cascade::Storage(MaxStages, m_stages);
  }

private:
  int MaxStages;
  Iir::Cascade::Stage *m_stages;
  Iir::DirectFormII *m_states;
};

// de-templatized for pimpl idom
// comes from iir from Bernd Porr
class PoleFilter : Iir::Butterworth::LowPassBase, public CascadeStages {
public:
  PoleFilter(int MaxPoles) : CascadeStages((MaxPoles + 1) / 2) {
    this->MaxPoles = MaxPoles;
    m_analogStorage = new LayoutStorage(MaxPoles);
    m_digitalStorage = new LayoutStorage(MaxPoles);
    // This glues together the factored base classes
    // with the templatized storage classes.
    Iir::Butterworth::LowPassBase::setCascadeStorage(this->getCascadeStorage());
    Iir::Butterworth::LowPassBase::setPrototypeStorage(*m_analogStorage,
                                                       *m_digitalStorage);
  }
  ~PoleFilter() {
    delete m_analogStorage;
    delete m_digitalStorage;
  }
  void setup(double sampleRate, double cutoffFrequency) {
    Iir::Butterworth::LowPassBase::setup(MaxPoles, sampleRate, cutoffFrequency);
  }

private:
  int MaxPoles;
  LayoutStorage *m_analogStorage;
  LayoutStorage *m_digitalStorage;
};

class ButterworthLowPass_impl {
public:
  ButterworthLowPass_impl(flair::filter::ButterworthLowPass *self,
                          const flair::gui::LayoutPosition *position,
                          std::string name, int order);
  ~ButterworthLowPass_impl();
  void UpdateFrom(const flair::core::io_data *data);
  flair::core::cvmatrix *output;

private:
  flair::gui::DoubleSpinBox *cutoff, *T;
  PoleFilter *f;
  bool first_update;
  flair::core::Time previous_time;
};

#endif // BUTTERWORTHLOWPASS_H_IMPL_H
