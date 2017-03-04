// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/03/27
//  filename:   Castle.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    classe chargeant une map chateau
//
/*********************************************************************/

#ifndef CASTLE_H
#define CASTLE_H

#include <Gui.h>
namespace flair {
namespace simulator {
class Castle : public Gui {
public:
  Castle(const flair::simulator::Simulator *parent, int app_width,
         int app_height, int scene_width, int scene_height,
         std::string media_path);
  ~Castle();

private:
};
} // end namespace simulator
} // end namespace flair
#endif // CASTLE_H
