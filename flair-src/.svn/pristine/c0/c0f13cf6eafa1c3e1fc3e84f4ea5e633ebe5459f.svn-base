// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
#include "ConnectionLayout.h"
#include "UdtSocket.h"
#include "DataRemote.h"
#include <qendian.h>
#include "communication.h"
#include <zlib.h>
#include <assert.h>

#define COMPRESS_CHUNK 1024
#define RX_TIME 5000

ConnectionLayout::ConnectionLayout(UdtSocket *socket, QString name)
    : Layout(NULL, name, "root") {
  isRemoteNameDefined = false;
  this->socket = socket;

  total_received=0;
  receive_timer = new QTimer(this);
  connect(receive_timer, SIGNAL(timeout()), this, SLOT(computeRxRate()));
  receive_timer->start(RX_TIME);
}

ConnectionLayout::~ConnectionLayout() {
  receive_timer->stop();
}

void ConnectionLayout::computeRxRate(void) {
  float receive_rate=((float)total_received/(RX_TIME/1000))/1000;//in Ko/s
  total_received=0;
  computedRxRate(receive_rate);
}

void ConnectionLayout::receive(char *buf, int size) {
  total_received+=size-1;
  // printf("trame %x\n",buf[0]);
  // for(int i=0; i<size;i++) printf("%x ",buf[i]);
  // printf("\n");
  switch (buf[0]) {
  case ZLIB_HEADER: {
    ssize_t out_size;
    char *uncompressbuf;
    uncompressBuffer(buf, size, &uncompressbuf, &out_size);
    handleUncompressedFrame(uncompressbuf, out_size);
    free(uncompressbuf);
    break;
  }
  default:
    handleUncompressedFrame(buf, size);
  }
  free(buf);
}

void ConnectionLayout::XmlToSend(QDomDocument doc) {
  // printf("xml to send\n%s\n",doc.toString().toLocal8Bit().constData());
  // xml to send a mettre dans le manager
  QMetaObject::invokeMethod(
      socket, "write", Qt::BlockingQueuedConnection,
      Q_ARG(const char *, doc.toString().toLocal8Bit().constData()),
      Q_ARG(qint64, doc.toString().toLocal8Bit().length()));
}

void ConnectionLayout::LoadXml(QDomDocument to_parse) {
  if (!isRemoteNameDefined) {
    printf("load xml: name not defined!\n");
    return;
  }

  QDomElement tmp = to_parse.firstChildElement("root");
  while (tmp.attribute("name") != remoteName && !tmp.isNull())
    tmp = to_parse.nextSiblingElement("root");

  if (!tmp.isNull()) {
    XmlWidget::LoadXml(tmp);
  } else {
    printf("%s not found in xml file \n", remoteName.toLocal8Bit().constData());
  }
}

void ConnectionLayout::handleUncompressedFrame(char *buf, ssize_t size) {
  switch ((unsigned char)buf[0]) {
  case XML_HEADER: {
    QString xml;
    QDomDocument doc;
    xml = QString((char *)buf);
    xml.resize(size);

    // printf("recu %i\n%s\n",size,xml.toLocal8Bit().constData());
    if (!doc.setContent(xml)) {
      printf("prob setContent fichier\n");
    }

    if (!isRemoteNameDefined) {
      isRemoteNameDefined = true;
      remoteName = doc.firstChildElement("root").attribute("name");
      setRemoteName(remoteName);
      SetAttribute("name", remoteName);
    }

    ParseXml(doc.firstChildElement("root").firstChildElement());
    break;
  }
  case DATAS_BIG_ENDIAN: {
    // for(int i=0;i<size;i++) printf("%x ",buf[i]);
    // printf("\n");
    uint16_t period;
    memcpy(&period, &buf[1], sizeof(uint16_t));
    period = qFromBigEndian(period);
    drawDatas(&buf[3], size - 3, period, true);
    break;
  }
  case DATAS_LITTLE_ENDIAN: {
    // for(int i=0;i<size;i++) printf("%x ",buf[i]);
    // printf("\n");
    uint16_t period;
    memcpy(&period, &buf[1], sizeof(uint16_t));
    // printf("recu %i period %i\n",size,period);
    drawDatas(&buf[3], size - 3, period);
    break;
  }
  default:
    printf("trame non supportée %x\n", buf[0]);
  }
}

void ConnectionLayout::removeDataRemote(DataRemote *data) {
  dataremotes.removeOne(data);
}

void ConnectionLayout::addDataRemote(DataRemote *data) {
  dataremotes.append(data);
}

QString ConnectionLayout::getRemoteName() { return remoteName; }
void ConnectionLayout::drawDatas(char *buf, int buf_size, uint16_t period,
                                 bool big_endian) {
  for (int i = 0; i < dataremotes.count(); i++) {
    dataremotes.at(i)->BufEvent(&buf, &buf_size, period, big_endian);
  }
}

int ConnectionLayout::uncompressBuffer(char *in, ssize_t in_size, char **out,
                                       ssize_t *out_size) {
  int ret;
  unsigned have;
  z_stream strm;

  // allocate inflate state
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = 0;
  strm.next_in = Z_NULL;
  ret = inflateInit(&strm);
  if (ret != Z_OK)
    return ret;

  *out = (char *)malloc(COMPRESS_CHUNK);
  if (!(*out))
    return Z_BUF_ERROR;

  strm.avail_in = in_size;
  strm.next_in = (unsigned char *)in;
  strm.avail_out = COMPRESS_CHUNK;
  strm.next_out = (unsigned char *)*out;

  ret = inflate(&strm, Z_NO_FLUSH);
  assert(ret != Z_STREAM_ERROR); // state not clobbered
  switch (ret) {
  case Z_NEED_DICT:
    ret = Z_DATA_ERROR; // and fall through
  case Z_DATA_ERROR:
  case Z_MEM_ERROR:
    (void)inflateEnd(&strm);
    return ret;
  }
  have = COMPRESS_CHUNK - strm.avail_out;
  *out_size = have;

  // printf("%i -> %i\n",in_size,have);
  // printf("%s\n",*out);
  // clean up and return
  (void)inflateEnd(&strm);
  return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}
