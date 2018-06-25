#include "HttpException.h"
#ifndef HTTPINETCONNECTION_H
#define HTTPINETCONNECTION_H
class HttpInetConnection : public HttpConnection {
    public:
        virtual ~HttpInetConnection() = 0;
        virtual TCPAddr getLocalAddress() = 0;
        virtual int getLocalPort() const = 0;
        virtual TCPAddr getRemoteAddress() = 0;
        virtual int getRemotePort() const = 0;
};
#endif
