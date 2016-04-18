// Copyright

#include <cstdlib>
#include <iostream>
#include <string>
#include <thread>

#include <boost/asio.hpp>

#include "common/message.h"
#include "common/protocol.h"


using boost::asio::ip::tcp;


void StartClientSession(tcp::socket sock) {
  try {
    const std::string &request = becho::Message::ReceiveMessage(&sock);
    std::cout << "request: " << request << std::endl;

    std::string response{becho::Protocol::kSuccessResponse};
    becho::Message::SendMessage(&sock, response);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}


int main(int argc, char *argv[]) {
  if (argc != 2) {
    return -1;
  }

  uint16_t port{static_cast<uint16_t>(::atoi(argv[1]))};

  boost::asio::io_service io_service;
  tcp::acceptor accpt{io_service, {tcp::v4(), port}};
  while (true) {
    tcp::socket sock{io_service};
    accpt.accept(sock);
    std::thread{StartClientSession, std::move(sock)}.detach();
  }

  return 0;
}
