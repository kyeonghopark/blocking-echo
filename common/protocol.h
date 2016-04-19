// Copyright

#ifndef COMMON_PROTOCOL_H_
#define COMMON_PROTOCOL_H_

#include <functional>

namespace becho {
class Protocol {
 public:
  using MessageHeader = unsigned long;  // NOLINT
  using NetConvertFunction = std::function<MessageHeader (MessageHeader)>;
  static const NetConvertFunction ntoh;
  static const NetConvertFunction hton;

  static const char *const kFileAttached;
  static const char *const kNoFileAttached;

  static const char *const kSuccessResponse;
};
}  // namespace becho

#endif  // COMMON_PROTOCOL_H_
