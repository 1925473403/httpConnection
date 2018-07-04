#include "HttpException.h"
#ifndef SOCKETFACTORY_H
#define SOCKETFACTORY_H
class SocketFactory {
    public:
    virtual ~SocketFactory() { }
    virtual Socket *createSocket() = 0;
    virtual Socket *connectSocket(Socket *sock, std::string host, int port, InetAddress *localAddress, int localPort, HttpParams *params) throw (IOException) = 0;
    virtual bool isSecure(Socket *_sock) = 0;
};
#endif
