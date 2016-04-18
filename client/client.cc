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
                 const std::string &request) {
  boost::asio::io_service io;
  tcp::socket sock{io};
  tcp::resolver resol{io};
  boost::asio::connect(sock, resol.resolve({host, service}));

  becho::Message::SendMessage(&sock, request);
  const std::string &response = becho::Message::ReceiveMessage(&sock);
  if (response != becho::Protocol::kSuccessResponse) {
    std::cerr << "response: " << response << std::endl;
    return;
  }
  std::cout << "response: " << response << std::endl;
}
}  // namespace becho
