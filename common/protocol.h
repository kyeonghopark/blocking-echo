#ifndef COMMON_PROTOCOL_H_
#define COMMON_PROTOCOL_H_

#include <functional>

namespace becho {
class Protocol {
 public:
  static const std::size_t kMaxMessageSize{1024};

  using MessageHeader = unsigned short;
  using NetConvertFunction = std::function<MessageHeader (MessageHeader)>;
  static const NetConvertFunction ntoh;
  static const NetConvertFunction hton;

  static const char *const kSuccessResponse;
};
}  // namespace becho

#endif  // COMMON_PROTOCOL_H_
