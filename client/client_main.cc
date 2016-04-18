// Copyright

#include <iostream>
#include <string>
#include "boost/asio.hpp"

#include "common/message.h"
#include "common/protocol.h"


using boost::asio::ip::tcp;


int main(int argc, char *argv[]) {
  if (argc != 4) {
    return -1;
  }

  std::string host{argv[1]};
  std::string svc{argv[2]};
  std::string request{argv[3]};

  boost::asio::io_service io;
  tcp::socket sock{io};
  tcp::resolver resol{io};
  boost::asio::connect(sock, resol.resolve({host, svc}));

  becho::Message::SendMessage(&sock, request);
  const std::string &response = becho::Message::ReceiveMessage(&sock);
  if (response != becho::Protocol::kSuccessResponse) {
    return -1;
  }
  std::cout << "response: " << response << std::endl;

  return 0;
}
