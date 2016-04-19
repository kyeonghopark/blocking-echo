// Copyright

#ifndef COMMON_MESSAGE_H_
#define COMMON_MESSAGE_H_

#include <string>
#include <tuple>
#include "boost/asio/ip/tcp.hpp"


using boost::asio::ip::tcp;


namespace becho {
class Message {
 public:
  static void SendMessage(tcp::socket *sock,
                          const std::string &msg,
                          const std::string &file_name);
  static std::tuple<std::string/*msg*/, std::string/*file_name*/>
      ReceiveMessage(tcp::socket *sock);

 private:
  static bool SendFile(tcp::socket *sock, const std::string &file_name);
  static std::tuple<bool/*result*/, std::string/*file_name*/>
      ReceiveFile(tcp::socket *sock);

  static void SendString(tcp::socket *sock, const std::string &str);
  static std::string ReceiveString(tcp::socket *sock);

  static void SendBytes(tcp::socket *sock,
                        const char *buf,
                        const std::size_t &buf_size);
  static std::string ReceiveBytes(tcp::socket *sock,
                                  const std::size_t &buf_size);

  static std::string ReadFile(const std::string &file_name);
  static bool WriteFile(const std::string &file_name,
                        const std::string &file_buf);
};
}  // namespace becho

#endif  // COMMON_MESSAGE_H_
