#ifndef BLOCKING_ECHO_SERVICE_COMMON_MESSAGE_H_
#define BLOCKING_ECHO_SERVICE_COMMON_MESSAGE_H_

#include <string>
#include <boost/asio.hpp>


using boost::asio::ip::tcp;


namespace becho {
class Message {
 public:
  static void SendMessage(tcp::socket *sock, const std::string &msg);
  static std::string ReceiveMessage(tcp::socket *sock);

 private:
  static void SendBytes(tcp::socket *sock,
                        const char *buf,
                        const std::size_t &buf_size);
  static std::string ReceiveBytes(tcp::socket *sock,
                                  const std::size_t &buf_size);
};
}  // namespace becho

#endif  // BLOCKING_ECHO_SERVICE_COMMON_MESSAGE_H_
