// Copyright

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include "boost/asio/ip/tcp.hpp"


using boost::asio::ip::tcp;


namespace becho {
class Server {
 public:
  void Run(const uint16_t &port);

 private:
  static void StartClientSession(tcp::socket socket);
};
}  // namespace becho

#endif  // SERVER_SERVER_H_
