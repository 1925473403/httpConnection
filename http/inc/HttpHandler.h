#include "HttpException.h"
#ifndef HTTPHANDLER_H
#define HTTPHANDLER_H
class HttpHandler : public URLStreamHandler {
    protected:
        std::string proxy;
        int proxyport;
        int getDefaultPort();
    public:
        HttpHandler();
        HttpHandler(std::string p, int port);
        HttpHandler(const HttpHandler &rhs);
        HttpHandler& operator=(const HttpHandler &rhs);
};
#endif
