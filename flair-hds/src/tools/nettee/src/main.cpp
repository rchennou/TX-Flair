#include <SocketManager.h>
#include <tclap/CmdLine.h>
#include <iostream>

using namespace TCLAP;
using namespace std;

int port;
string address;
int localPort;
int expectedClientNumber;
bool wait;

void ParseOptions(int argc, char **argv) {
  try {
    CmdLine cmd("Establishes a tcp connection to a given distant host and "
                "port, then repeats everything read through that connection to "
                "any remote host connected on the local host (by default on "
                "the same port)",
                ' ', "0.1");
    ValueArg<int> portArg("p", "port", "port to connect to", true, 5555,
                          "integer", cmd);
    ValueArg<string> addressArg("a", "address", "address to connect to", true,
                                "127.0.0.1", "ip address", cmd);
    ValueArg<int> localPortArg("l", "local_port", "local port we listen on",
                               false, 0, "integer", cmd);
    ValueArg<int> clientNumberArg(
        "n", "client_number", "number of clients to wait for before starting",
        false, 1, "integer", cmd);
    SwitchArg waitArg("w", "wait", "wait for the number of clients specified by -n to connect to the server address", cmd);
    cmd.parse(argc, argv);

    // Get the value parsed by each arg.
    port = portArg.getValue();
    address = addressArg.getValue();
    localPort = localPortArg.getValue();
    if (localPort == 0)
      localPort = port;
    expectedClientNumber = clientNumberArg.getValue();
    wait=waitArg.getValue();

  } catch (ArgException &e) {
    cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
  }
}

int main(int argc, char** argv) {
  ParseOptions(argc, argv);
  SocketManager *socketManager = new SocketManager(address,port,localPort,expectedClientNumber,wait);
  socketManager->Run();
  delete socketManager;
  return 0;
}
