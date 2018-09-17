#include "HttpException.h"
#include "RefCount.h"
#ifndef HTTPREQUESTHANDLER_H
#define HTTPREQUESTHANDLER_H
class HttpRequestHandler : public RefCount {
    public:
    virtual ~HttpRequestHandler() { }
    virtual void handle(HttpRequest *request, HttpResponse *resposne, HttpContext *context) throw (HttpException, IOException) = 0;
};
#endif
