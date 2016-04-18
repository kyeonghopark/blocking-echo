// Copyright

#include "server/server.h"
#include <cstdlib>


int main(int argc, char *argv[]) {
  if (argc != 2) {
    return -1;
  }

  uint16_t port{static_cast<uint16_t>(::atoi(argv[1]))};

  becho::Server server;
  server.Run(port);

  return 0;
}
