// Copyright

#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_

#include <string>


namespace becho {
class Client {
 public:
  void Run(const std::string &host,
           const std::string &service,
           const std::string &request,
           const std::string &file_name);
};
}  // namespace becho
#endif  // CLIENT_CLIENT_H_
