// Copyright

#include "common/message.h"

#include <algorithm>
#include <fstream>
#include "boost/asio/read.hpp"
#include "boost/asio/socket_base.hpp"
#include "boost/asio/write.hpp"

#include "common/protocol.h"


namespace becho {
void Message::SendMessage(tcp::socket *sock,
                          const std::string &msg,
                          const std::string &file_name) {
  SendString(sock, msg);
  if (file_name.empty()) {
    SendString(sock, Protocol::kNoFileAttached);
  } else {
    SendString(sock, Protocol::kFileAttached);
    SendFile(sock, file_name);
  }
}


std::tuple<std::string/*msg*/, std::string/*file_name*/>
    Message::ReceiveMessage(tcp::socket *sock) {
  std::string msg{ReceiveString(sock)};
  std::string file_attached{ReceiveString(sock)};
  std::string file_name{""};
  if (file_attached == Protocol::kFileAttached) {
    bool result{false};
    std::tie(result, file_name) = ReceiveFile(sock);
  }
  return std::make_tuple(std::move(msg), std::move(file_name));
}


bool Message::SendFile(tcp::socket *sock, const std::string &file_name) {
  std::string file_buf{ReadFile(file_name)};
  if (file_buf.empty()) {
    return false;
  }
  SendString(sock, file_name);
  SendString(sock, file_buf);
  return true;
}


std::tuple<bool/*result*/, std::string/*file_name*/>
    Message::ReceiveFile(tcp::socket *sock) {
  std::string file_name{ReceiveString(sock)};
  if (file_name.empty()) {
    return std::make_tuple(false, "");
  }
  std::string file_buf{ReceiveString(sock)};
  bool result{WriteFile(file_name, file_buf)};
  return std::make_tuple(result, file_name);
}


void Message::SendString(tcp::socket *sock, const std::string &str) {
  Protocol::MessageHeader net_size{
      Protocol::hton(
          static_cast<Protocol::MessageHeader>(str.size()))};
  SendBytes(sock, reinterpret_cast<char *>(&net_size), sizeof(net_size));
  SendBytes(sock, str.c_str(), str.size());
}


std::string Message::ReceiveString(tcp::socket *sock) {
  std::string net_size{
      ReceiveBytes(sock, sizeof(Protocol::MessageHeader))};
  std::size_t str_size{
      Protocol::ntoh(
          *reinterpret_cast<const Protocol::MessageHeader *>(
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


std::string Message::ReadFile(const std::string &file_name) {
  std::ifstream fs{file_name, (std::ios::in | std::ios::binary)};
  if (!fs) {
    return "";
  }
  fs.seekg(0, std::ios::end);
  std::size_t file_size{static_cast<std::size_t>(fs.tellg())};
  std::string file_buf;
  file_buf.resize(file_size);
  fs.seekg(0, std::ios::beg);
  fs.read(&file_buf[0], file_size);
  fs.close();
  return std::move(file_buf);
}


bool Message::WriteFile(const std::string &file_name,
                        const std::string &file_buf) {
  std::ofstream fs{file_name, (std::ios::out | std::ios::binary)};
  if (!fs) {
    return false;
  }
  fs.write(file_buf.data(), file_buf.size());
  fs.close();
  return true;
}


const Message::Protocol::NetConvertFunction Message::Protocol::ntoh{::ntohl};
const Message::Protocol::NetConvertFunction Message::Protocol::hton{::htonl};

const char *const Message::Protocol::kFileAttached{"FileAttached"};
const char *const Message::Protocol::kNoFileAttached{"NoFileAttached"};
}  // namespace becho
