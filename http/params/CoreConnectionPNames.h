#include "HttpException.h"
#ifndef CORECONNECTIONPNAMES_H
#define CORECONNECTIONPNAMES_H
class CoreConnectionPNames {
    public:
    CoreConnectionPNames () { }
    virtual ~CoreConnectionPNames() { }
    static std::string _SO_TIMEOUT;
    static std::string _TCP_NODELAY;
    static std::string _SOCKET_BUFFER_SIZE;
    static std::string _SO_LINGER;
    static std::string _CONNECTION_TIMEOUT;
    static std::string _STALE_CONNECTION_CHECK;
    static std::string _MAX_LINE_LENGTH;
    static std::string _MAX_HEADER_COUNT;
};
#endif
