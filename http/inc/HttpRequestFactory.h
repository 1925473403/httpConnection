#include "HttpException.h"
#ifndef HTTPREQUESTFACTORY_H
#define HTTPREQUESTFACTORY_H
class HttpRequestFactory {
    public:
    virtual ~HttpRequestFactory() { }
    virtual HttpRequest *newHttpRequest(RequestLine *requestline) throw (MethodNotSupportedException) = 0;
    virtual HttpRequest *newHttpRequest(std::string method, std::string uri) throw(MethodNotSupportedException) = 0;
};
#endif
