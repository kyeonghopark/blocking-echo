#ifndef BLOCKING_ECHO_SERVICE_COMMON_PROTOCOL_H_
#define BLOCKING_ECHO_SERVICE_COMMON_PROTOCOL_H_

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

#endif  // BLOCKING_ECHO_SERVICE_COMMON_PROTOCOL_H_
