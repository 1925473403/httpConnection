#include "HttpException.h"
#ifndef SOCKET_H
#define SOCKET_H
class Socket {
    private:
    SocketImpl *impl;
    public:
    Socket();
    void createImpl();
};
#endif
