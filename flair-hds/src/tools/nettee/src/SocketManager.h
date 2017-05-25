#include <string>
#include <poll.h>
#include <list>
#include <fstream>

class SocketManager {
public:
  SocketManager(std::string address,int port,int localPort,int expectedClientNumber,bool wait);
  ~SocketManager();
  void Run();

private:
  void SetupPollStruct(struct pollfd **fds,nfds_t *nfds);
  void PrintPollFlags(short revents);
  bool ConnectUpstream();
  void AcceptNewClient();
  void ProcessData();
  void RemoveClient(int downstreamSocket);
  void ProcessClient(int downstreamSocket);
  void HandleSocket(const struct pollfd &pollfd);
  void Cleanup();
  void InitListeningSocket();
  int SetupListeningSocket();
  int SetBlocking(int fd,bool val);

  std::string address;
  int port,localPort,expectedClientNumber;
  bool mustWait;
  int clientNumber;
  int *listeningSocket;
  int *upstreamSocket;
  std::list<int> downstreamSockets;
  bool jobDone;
  char buffer[4096];
    std::ofstream logFile;
};
