// Copyright

#include "client/client.h"
#include <string>


int main(int argc, char *argv[]) {
  if (argc < 4) {
    return -1;
  }

  std::string host{argv[1]};
  std::string svc{argv[2]};
  std::string request{argv[3]};
  std::string file_name{(argc >= 5) ? argv[4] : ""};

  becho::Client client;
  client.Run(host, svc, request, file_name);

  return 0;
}
