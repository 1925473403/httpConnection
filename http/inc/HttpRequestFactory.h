#include "HttpException.h"
#ifndef HTTPREQUESTFACTORY_H
#define HTTPREQUESTFACTORY_H
class HttpRequestFactory {
    public:
    virtual ~HttpRequestFactory() = 0;
    virtual HttpRequest *newHttpRequest(RequestLine *requestline) throw (MethodNotSupportedException) = 0;
    virtual HttpRequest *newHttpRequest(std::string method, std::string uri) throws MethodNotSupportedException= 0;
};
#endif
