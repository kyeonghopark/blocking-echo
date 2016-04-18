// Copyright

#include "common/protocol.h"
#include "boost/asio/socket_base.hpp"


namespace becho {
const Protocol::NetConvertFunction Protocol::ntoh{::ntohs};
const Protocol::NetConvertFunction Protocol::hton{::htons};

const char *const Protocol::kSuccessResponse{"ok"};
}  // namespace becho
