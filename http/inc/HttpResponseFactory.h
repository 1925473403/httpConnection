#include "HttpException.h"
#ifndef HTTPRESPONSEFACTORY_H
#define HTTPRESPONSEFACTORY_H
class HttpResponseFactory {
    public:
    virtual ~HttpResponseFactory() { }
    virtual HttpResponse *newHttpResponse(ProtocolVersion *ver, int status, HttpContext *context) = 0;
    virtual HttpResponse *newHttpResponse(StatusLine *statline, HttpContext *context) = 0;
};
#endif
