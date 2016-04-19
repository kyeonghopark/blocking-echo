// Copyright

#include "client/client.h"

#include <iostream>

#include "boost/asio/connect.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "boost/asio/io_service.hpp"

#include "common/message.h"
#include "common/protocol.h"

using boost::asio::ip::tcp;


namespace becho {
void Client::Run(const std::string &host,
                 const std::string &service,
                 const std::string &request,
                 const std::string &file_name) {
  boost::asio::io_service io;
  tcp::socket sock{io};
  tcp::resolver resol{io};
  boost::asio::connect(sock, resol.resolve({host, service}));

  becho::Message::SendMessage(&sock, request, file_name);
  std::string response;
  std::string response_file;
  std::tie(response, response_file) = becho::Message::ReceiveMessage(&sock);
  if (response != becho::Protocol::kSuccessResponse) {
    std::cerr << "response fail: " << response << std::endl;
    return;
  }
  std::cout << "response: " << response
            << "response_file: " << response_file << std::endl;
}
}  // namespace becho
