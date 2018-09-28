#include "HttpException.h"
#include "RefCount.h"
#ifndef HTTPRESPONSEFACTORY_H
#define HTTPRESPONSEFACTORY_H
class ProtocolVersion;
class HttpContext;
class StatusLine;
class HttpResponse;
class HttpResponseFactory : public RefCount {
    public:
    virtual ~HttpResponseFactory() { }
    virtual HttpResponse *newHttpResponse(ProtocolVersion *ver, int status, HttpContext *context) = 0;
    virtual HttpResponse *newHttpResponse(StatusLine *statline, HttpContext *context) = 0;
};
#endif
