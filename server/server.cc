// Copyright

#include "server/server.h"

#include <iostream>
#include <string>
#include <thread>  // NOLINT

#include "common/message.h"
#include "common/protocol.h"


namespace becho {
void Server::StartClientSession(tcp::socket sock) {
  try {
    const std::string &request = becho::Message::ReceiveMessage(&sock);
    std::cout << "request: " << request << std::endl;

    std::string response{becho::Protocol::kSuccessResponse};
    becho::Message::SendMessage(&sock, response);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}


void Server::Run(const uint16_t &port) {
  boost::asio::io_service io_service;
  tcp::acceptor accpt{io_service, {tcp::v4(), port}};

  while (true) {
    tcp::socket sock{io_service};
    accpt.accept(sock);
    std::thread{&Server::StartClientSession, std::move(sock)}.detach();
  }
}
}  // namespace becho
