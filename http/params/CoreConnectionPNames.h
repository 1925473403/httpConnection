#include "HttpException.h"
#ifndef CORECONNECTIONPNAMES_H
#define CORECONNECTIONPNAMES_H
class CoreConnectionPNames {
    public:
    CoreConnectionPNames () { }
    static std::string SO_TIMEOUT;
    static std::string TCP_NODELAY;
    static std::string SOCKET_BUFFER_SIZE;
    static std::string SO_LINGER;
    static std::string CONNECTION_TIMEOUT;
    static std::string STALE_CONNECTION_CHECK;
    static std::string MAX_LINE_LENGTH;
    static std::string MAX_HEADER_COUNT;
};
#endif
