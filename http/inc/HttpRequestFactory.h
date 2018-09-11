#include "HttpException.h"
#include "RefCount.h"
#ifndef HTTPREQUESTFACTORY_H
#define HTTPREQUESTFACTORY_H
class HttpRequestFactory : public RefCount {
    public:
    virtual ~HttpRequestFactory() { }
    virtual HttpRequest *newHttpRequest(RequestLine *requestline) throw (MethodNotSupportedException) = 0;
    virtual HttpRequest *newHttpRequest(std::string method, std::string uri) throw(MethodNotSupportedException) = 0;
};
#endif
