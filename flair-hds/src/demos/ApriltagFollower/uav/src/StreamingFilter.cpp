//  created:    2017/01/26
//  filename:   StreamingFilter.cpp
//
//  author:     Thomas Fuhrmann
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    StreamingFilter image flow over socket
//
//
/*********************************************************************/

#include "StreamingFilter.h"
#include <cvimage.h>
#include <TcpSocket.h>
#include <FrameworkManager.h>

using std::string;
using namespace flair::core;

namespace flair {
namespace filter {

StreamingFilter::StreamingFilter(const core::IODevice *parent, std::string name, std::string ipAddress,
                               int ipPort) :  IODevice(parent, name), suspendFlag(false) {
  // Socket stuff
  sendingSocket = new TcpSocket(getFrameworkManager(), "SndSkt", true, true);

  if (!sendingSocket->Connect(ipPort, ipAddress)) {
      Err("sendingSocket connect failed\n");
  }
}

StreamingFilter::~StreamingFilter(void) {
}

void StreamingFilter::UpdateFrom(const io_data *data) {
  cvimage *output = (cvimage *) data;
  IplImage *img = ((cvimage *) data)->img;
  int bytesSend = 0;
  int imageSize = img->width * img->height * img->nChannels;
  if (!suspendFlag) {
      data->GetMutex();
      if ((bytesSend = sendingSocket->SendMessage(img->imageData, imageSize, 0)) < 0) {
//                    if (bytesSend != -1) {
//                        Warn("Only %d bytes...\n", bytesSend);
//                    } else {
//                        Err("StreamingFiltert socket error... Suspend the process.\n");
//                        suspendFlag = true;
//                    }
          Warn("Only %d bytes...\n", bytesSend);
      }
      Time time=data->DataTime();
      if ((bytesSend = sendingSocket->SendMessage((char*)&time, sizeof(Time), 0)) < 0) {
          Warn("Only %d/%d bytes...\n", bytesSend,sizeof(Time));
      }
      data->ReleaseMutex();
  }
  output->SetDataTime(data->DataTime());
  ProcessUpdate(output);
}

} // end namespace filter
} // end namespace flair
