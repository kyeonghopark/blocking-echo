// Copyright

#include "client/client.h"
#include <string>


int main(int argc, char *argv[]) {
  if (argc != 4) {
    return -1;
  }

  std::string host{argv[1]};
  std::string svc{argv[2]};
  std::string request{argv[3]};

  becho::Client client;
  client.Run(host, svc, request);

  return 0;
}
