// Copyright

#include "common/protocol.h"
#include "boost/asio/socket_base.hpp"


namespace becho {
const Protocol::NetConvertFunction Protocol::ntoh{::ntohl};
const Protocol::NetConvertFunction Protocol::hton{::htonl};

const char *const Protocol::kFileAttached{"FileAttached"};
const char *const Protocol::kNoFileAttached{"NoFileAttached"};

const char *const Protocol::kSuccessResponse{"ok"};
}  // namespace becho
