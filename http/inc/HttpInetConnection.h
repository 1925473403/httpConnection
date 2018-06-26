#include "HttpException.h"
#ifndef HTTPINETCONNECTION_H
#define HTTPINETCONNECTION_H
class HttpInetConnection : public HttpConnection {
    public:
        virtual ~HttpInetConnection() { }
        virtual TCPAddr getLocalAddress() = 0;
        virtual int getLocalPort() = 0;
        virtual TCPAddr getRemoteAddress() = 0;
        virtual int getRemotePort() = 0;
};
#endif
