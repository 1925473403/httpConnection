#include "HttpException.h"
#ifndef HTTPSHANDLER_H
#define HTTPSHANDLER_H
class HttpsHandler : public URLStreamHandler {
    protected:
        std::string proxy;
        int proxyport;
        int getDefaultPort();
    public:
        HttpsHandler();
        HttpsHandler(std::string p, int port);
        HttpsHandler(const HttpsHandler &rhs);
        HttpsHandler& operator=(const HttpsHandler &rhs);
};
#endif
