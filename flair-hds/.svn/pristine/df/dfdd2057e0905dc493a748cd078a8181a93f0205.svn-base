#include "SocketManager.h"

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <assert.h>

#define TIMEOUT 500
using namespace std;

SocketManager::SocketManager(string address,int port,int localPort,int expectedClientNumber,bool mustWait):address(address),port(port),localPort(localPort),expectedClientNumber(expectedClientNumber),mustWait(mustWait),clientNumber(0),upstreamSocket(nullptr), jobDone(false) {
  logFile.open("/var/log/rtcm",ios::out|ios::app);
  logFile << "<-------------------" << endl;
  InitListeningSocket();
}

SocketManager::~SocketManager() {
    logFile << "------------------->" << endl;
    logFile.close();
}

void SocketManager::SetupPollStruct(struct pollfd **fds,nfds_t *nfds) {
  nfds_t socketNumber=0;
  if (listeningSocket) socketNumber++;
  if (upstreamSocket) socketNumber++;
  socketNumber+=downstreamSockets.size();
  *fds=new struct pollfd[socketNumber];

  int i=0;
  if (listeningSocket) {
    (*fds)[i].fd=*listeningSocket;
    (*fds)[i].events=POLLIN;
    i++;
  } if (upstreamSocket) {
    (*fds)[i].fd=*upstreamSocket;
    (*fds)[i].events=POLLIN;
    i++;
  }
  for (auto it = downstreamSockets.begin(); it != downstreamSockets.end();
    ++it) {
    (*fds)[i].fd=*it;
    (*fds)[i].events=POLLIN;
    i++;
  }
  *nfds=socketNumber;
}

void SocketManager::Run() {
  while (!jobDone) {
    struct pollfd *fds;
    nfds_t nfds;
    SetupPollStruct(&fds, &nfds);
    int pollResult = poll(fds, nfds, TIMEOUT);
    if (pollResult > 0) {
      for (int i = 0; i < nfds; i++)
        if (fds[i].revents) HandleSocket(fds[i]);
    } else if (pollResult == -1) {
      perror("poll failed. Error");
      Cleanup();
    }
  }
}

bool SocketManager::ConnectUpstream() {
  // Create socket
  upstreamSocket=new int;
  *upstreamSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (*upstreamSocket == -1) {
    perror("Could not create socket");
    return false;
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  // setup address structure
  if (inet_addr(address.c_str()) != -1) {
    server.sin_addr.s_addr = inet_addr(address.c_str());
  } else {
    // resolve the hostname, its not an ip address
    struct hostent *he;
    struct in_addr **addr_list;

    if ((he = gethostbyname(address.c_str())) == NULL) {
      herror("gethostbyname");
      logFile << "Failed to resolve hostname " << address << endl;
      return false;
    }

    // Cast the h_addr_list to in_addr , since h_addr_list also has the ip
    // address in long format only
    addr_list = (struct in_addr **)he->h_addr_list;
    for (int i = 0; addr_list[i] != NULL; i++) {
      // strcpy(ip , inet_ntoa(*addr_list[i]) );
      server.sin_addr = *addr_list[i];
      logFile << address << " resolved to " << inet_ntoa(*addr_list[i]) << endl;
      break;
    }
  }

  // Connect to remote server
  if (connect(*upstreamSocket, (struct sockaddr *)&server, sizeof(server)) <
      0) {
    perror("upstream server connexion failed. Error");
    close(*upstreamSocket);
    upstreamSocket=nullptr;
    return false;
  }

  SetBlocking(*upstreamSocket,false);
  return true;
}

void SocketManager::AcceptNewClient() {
  struct sockaddr_in client_addr;
  socklen_t size = sizeof(client_addr);
  int downstreamSocket =
      accept(*listeningSocket, reinterpret_cast<struct sockaddr *>(&client_addr),
             &size);
  if (downstreamSocket == -1) {
    perror("accept failed. Error");
    Cleanup();
  } else {
      downstreamSockets.push_back(downstreamSocket);
      clientNumber++;
      if (!mustWait && clientNumber==1) {
        if (!ConnectUpstream()) Cleanup();
      } else if (mustWait && (clientNumber == expectedClientNumber)) {
        shutdown(*listeningSocket, SHUT_RDWR);
        if (!ConnectUpstream()) Cleanup();
      }
  }
}

void SocketManager::ProcessData() {
  int bytesRead = read(*upstreamSocket, buffer, sizeof(buffer));
  if (bytesRead == 0) Cleanup();
  else if (bytesRead == -1) {
    perror("accept failed. Error");
    Cleanup();
  } else {
    for (auto it = downstreamSockets.begin(); it != downstreamSockets.end();
         ++it) {
      int bytesWritten = write(*it, buffer, bytesRead);
      if (bytesWritten != bytesRead) {
        logFile << "Error: written less bytes than read, giving up" << endl;
      }
    }
  }
}

void SocketManager::RemoveClient(int downstreamSocket) {
  for (auto it = downstreamSockets.begin(); it != downstreamSockets.end();
       ++it) {
    if (downstreamSocket == *it) {
        close(*it);
        it=downstreamSockets.erase(it);
        clientNumber--;
        break;
    }
  }
  if (clientNumber == 0) {
    Cleanup();
  }
}

void SocketManager::ProcessClient(int downstreamSocket) {
  //cerr << "process client on socket #" << downstreamSocket << endl;
  int bytesRead = read(downstreamSocket, buffer, sizeof(buffer));
  if (bytesRead == 0) {
    RemoveClient(downstreamSocket);
  } else {
    logFile << "Warning: clients are not expected to send data" << endl;
  }
}

void SocketManager::PrintPollFlags(short flags) {
    cout << ">> ";
    if (flags&POLLIN) cout << "POLLIN | ";
    if (flags&POLLOUT) cout << "POLLOUT | ";
    if (flags&POLLNVAL) cout << "POLLNVAL | ";
    if (flags&POLLHUP) cout << "POLLHUP | ";
    cout << "<<" << endl;
}

void SocketManager::HandleSocket(const struct pollfd &pollfd) {
  //cerr << "Called for socket #" << pollfd.fd << ". flags: " << endl;
  //PrintPollFlags(pollfd.revents);
  if (listeningSocket && (pollfd.fd == *listeningSocket)) {
    if (pollfd.revents&POLLHUP) {
      close(*listeningSocket);
      listeningSocket=nullptr;
    } else if (pollfd.revents&POLLIN) AcceptNewClient();
    return;
  }
  if (upstreamSocket && (pollfd.fd == *upstreamSocket)) {
    if (pollfd.revents&POLLIN) ProcessData();
  } else {
    if (pollfd.revents&POLLIN) ProcessClient(pollfd.fd);
  }
}

void SocketManager::Cleanup() {
  if (listeningSocket) {
    close(*listeningSocket);
    delete listeningSocket;
  }
  if (upstreamSocket) {
    shutdown(*upstreamSocket,SHUT_RDWR);
    SetBlocking(*upstreamSocket,true);
    int bytesRead = read(*upstreamSocket, buffer, sizeof(buffer));
    assert(bytesRead==0);
    close(*upstreamSocket);
    delete upstreamSocket;
  }
  for (auto it = downstreamSockets.begin(); it != downstreamSockets.end();
       ++it) {
    logFile << "Upstream closed. Waiting for downstream clients to close the connexion" << endl;
    SetBlocking(*it,true);
    int bytesRead = read(*it, buffer, sizeof(buffer));
    assert(bytesRead==0);
    close(*it);
    it=downstreamSockets.erase(it);
    clientNumber--;
  }
  jobDone=true;
}

void SocketManager::InitListeningSocket() {
  // Assume we're called from xinetd: listening socket is on standard input (and
  // output BTW)
  listeningSocket=new int;
  *listeningSocket=0;
  int isListeningSocket;
  size_t isListeningSocketSize=sizeof(isListeningSocket);

  int getsockoptResult=getsockopt(*listeningSocket, SOL_SOCKET, SO_ACCEPTCONN, (void *)&isListeningSocket,
             (socklen_t *)&isListeningSocketSize);
  if (getsockoptResult == -1) {
    // We're not called from xinetd: we should listen first
    *listeningSocket=SetupListeningSocket();
  }
  SetBlocking(*listeningSocket,false);
}

int SocketManager::SetupListeningSocket() {
  int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1) {
    cerr << "Could not create socket" << endl;
  }
  int trueVal=1;
  setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &trueVal, sizeof(trueVal));

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(localPort);
  if (bind(socket_desc, reinterpret_cast<struct sockaddr *>(&server),sizeof(server)) < 0) {
    perror("bind failed. error:");
    exit(1);
  }

  listen(socket_desc, expectedClientNumber);
  return socket_desc;
}

int SocketManager::SetBlocking(int fd,bool val) {
  if (val) {
    return fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) & ~O_NONBLOCK);
  } else {
    return fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
  }
}
