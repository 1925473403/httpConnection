#include "HttpException.h"
#ifndef HTTPREQUESTHANDLERRESOLVER_H
#define HTTPREQUESTHANDLERRESOLVER_H
class HttpRequestHandlerResolver {
    public:
        virtual ~HttpRequestHandlerResolver () { }
        HttpRequestHandler *lookup(std::string requestURI) = 0;
};
#endif
