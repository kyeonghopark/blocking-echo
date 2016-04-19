// Copyright

#include "server/server.h"

#include <iostream>
#include <sstream>
#include <string>
#include <thread>  // NOLINT

#include "common/message.h"
#include "common/protocol.h"


namespace becho {
void Server::Run(const uint16_t &port) {
  boost::asio::io_service io_service;
  tcp::acceptor accpt{io_service, {tcp::v4(), port}};

  while (true) {
    tcp::socket sock{io_service};
    accpt.accept(sock);
    std::thread{&Server::StartClientSession, std::move(sock)}.detach();
  }
}


void Server::StartClientSession(tcp::socket sock) {
  try {
    std::string request;
    std::string request_file;
    std::tie(request, request_file) = becho::Message::ReceiveMessage(&sock);
    std::cout << "request: " << request
              << "request_file: " << request_file << std::endl;

    std::string response_file{request_file + ".ECHO"};
    if (!request_file.empty()) {
      std::stringstream ss;
      ss << "MOVE /Y \"" << request_file << "\" \"" << response_file << "\"";
      std::system(ss.str().c_str());
    }

    std::string response{becho::Protocol::kSuccessResponse};
    becho::Message::SendMessage(&sock, response, response_file);
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
}  // namespace becho
