// Copyright

#include "common/protocol.h"
#include <boost/asio.hpp>


namespace becho {
const Protocol::NetConvertFunction Protocol::ntoh{::ntohs};
const Protocol::NetConvertFunction Protocol::hton{::htons};

const char *const Protocol::kSuccessResponse{"ok"};
}  // namespace becho
