// Copyright

#include "common/message.h"

#include <algorithm>
#include "boost/asio/read.hpp"
#include "boost/asio/write.hpp"

#include "common/protocol.h"


namespace becho {
void Message::SendMessage(tcp::socket *sock, const std::string &msg) {
  SendString(sock, msg);
}


std::string Message::ReceiveMessage(tcp::socket *sock) {
  std::string msg{ReceiveString(sock)};
  return std::move(msg);
}


void Message::SendString(tcp::socket *sock, const std::string &str) {
  becho::Protocol::MessageHeader net_size{
      becho::Protocol::hton(
          static_cast<becho::Protocol::MessageHeader>(str.size()))};
  SendBytes(sock, reinterpret_cast<char *>(&net_size), sizeof(net_size));
  SendBytes(sock, str.c_str(), str.size());
}


std::string Message::ReceiveString(tcp::socket *sock) {
  std::string net_size{
      ReceiveBytes(sock, sizeof(becho::Protocol::MessageHeader))};
  std::size_t str_size{
      becho::Protocol::ntoh(
          *reinterpret_cast<const becho::Protocol::MessageHeader *>(
              net_size.c_str()))};
  std::string str{ReceiveBytes(sock, str_size)};
  return std::move(str);
}


void Message::SendBytes(tcp::socket *sock,
                        const char *buf,
                        const std::size_t &buf_size) {
  boost::asio::write(*sock, boost::asio::buffer(buf, buf_size));
}


std::string Message::ReceiveBytes(tcp::socket *sock,
                                  const std::size_t &buf_size) {
  std::string msg;
  msg.resize(buf_size);
  boost::asio::read(*sock, boost::asio::buffer(&msg[0], buf_size));
  return std::move(msg);
}
}  // namespace becho
