// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
/*!
 * \file HokuyoUTM30Lx.h
 * \brief Classe intégrant le telemetre laser Hokuyo UTM 30lx
 * \author César Richard, Copyright Heudiasyc UMR UTC/CNRS 7253
 * \date 2014/07/22
 * \version 1.0
 */

#ifndef HOKUYOUTM30LX_H
#define HOKUYOUTM30LX_H

#include <Thread.h>
#include <LaserRangeFinder.h>
#include <Mutex.h>

#include <queue>
#include <vector>

namespace flair {
namespace core {
class cvmatrix;
class FrameworkManager;
class SerialPort;
class Mutex;
}
namespace gui {
class Tab;
class TabWidget;
class RangeFinderPlot;
}
}

namespace flair {
namespace sensor {
/*! \class HokuyoUTM30Lx
*
* \brief Classe intégrant le telemetre laser Hokuyo UTM 30lx
*/
class HokuyoUTM30Lx : public core::Thread, public LaserRangeFinder {
public:
  /*!
 * \brief Constructor
 *
 * Construct a Hokuyo UTM30-Lx.
 *
 * \param parent parent
 * \param name name
 * \param serialport serialport
 * \param priority priority of the Thread
 */
  HokuyoUTM30Lx(const core::FrameworkManager *parent, std::string name,
                core::SerialPort *serialport, uint8_t priority);
  void getMesure(int startStep, int endStep, int clusterCount, int interval,
                 int scanNumber = 0);
  core::cvmatrix *getDatas(void);

  /*!
  * \brief Use default plot
  *
  */
  void UseDefaultPlot(void);
  /*!
  * \brief Destructor
  *
  */
  ~HokuyoUTM30Lx();

private:
  core::SerialPort *serialport;
  core::Mutex *bufRetMut;
  core::Mutex *sendingCmdMut;
  gui::Tab *main_tab;
  gui::TabWidget *tab;
  gui::RangeFinderPlot *plot;

  // matrix
  core::cvmatrix *output;

  std::queue<std::string> bufRet;

  /*!
  * \brief Run function
  *
  * Reimplemented from Thread.
  *
  */
  void Run(void);
  /*!
  * \brief Send a command
  * \param command Command to send (see Hokuyo UTM 30-LX doc for more
  * informations)
  * \return Return code
  */
  std::string sendCommand(std::string command);
  /*!
  * \brief Start the laser
  *
  */
  void startLaser(void);
  /*!
  * \brief Stop the laser
  *
  */
  void stopLaser(void);
  /*!
* \brief Stop and reset the laser's settings
*
*/
  void resetConfig(void);
  /*!
* \brief Decode incomming datas
* \param datas Datas to decode
* \param startStep Set the first mesured point
* Decode mesured points from incoming datas and fill the output matrix
*/
  void decodeDatas(std::vector<std::string> datas, int startStep);
  /*!
  * \brief Explode a string into a vector
  * \param str The string to explode
  * \param delimiter The character separating elements
  * \return A vector containing the elements
  */
  static std::vector<std::string> explode(const std::string str,
                                          char delimiter);
  /*!
* \brief Calculate the checksum
* \param code Data from which calculate
* \param byte Data's size
* \return A character corresponding to the code's checksum
*/
  static int encodeSum(const char *code, int byte);
  /*!
* \brief Check if a data correspond to its checksum
* \param data Datas to check
*/
  static bool checkSum(std::string data);
  /*!
* \brief Decode datas using the 2 character encoding
* \param data Datas to decode
* \return Decoded datas
*/
  static float decode2car(const char *data);
  /*!
* \brief Decode datas using the 3 character encoding
* \param data Datas to decode
* \return Decoded datas
*/
  static float decode3car(const char *data);
  /*!
* \brief Decode datas using the 4 character encoding
* \param data Datas to decode
* \return Decoded datas
*/
  static float decode4car(const char *data);

  /*!
* \brief Update using provided datas
*
* Reimplemented from IODevice.
*
* \param data data from the parent to process
*/
  void UpdateFrom(const core::io_data *data){};
};
} // end namespace sensor
} // end namespace framewor
#endif // HOKUYOUTM30LX_H
