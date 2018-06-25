#include "HttpException.h"
#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
class HttpRequest : virtual public HttpMessage {
    public:
    virtual ~HttpRequest() { }
    virtual RequestLine* getRequestLine() = 0;
};
#endif
