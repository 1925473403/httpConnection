#include "HttpException.h"
#include "RefCount.h"
#ifndef HTTPREQUESTHANDLERRESOLVER_H
#define HTTPREQUESTHANDLERRESOLVER_H
class HttpRequestHandlerResolver : public RefCount {
    public:
        virtual ~HttpRequestHandlerResolver () { }
        virtual HttpRequestHandler *lookup(std::string &requestURI) = 0;
};
#endif
