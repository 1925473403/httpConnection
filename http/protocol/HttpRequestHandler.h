#include "HttpException.h"
#ifndef HTTPREQUESTHANDLER_H
#define HTTPREQUESTHANDLER_H
class HttpRequestHandler {
    public:
    virtual HttpProcessor() { }
    virtual handle(HttpRequest *request, HttpResponse *resposne, HttpContext *context) throw (HttpException, IOException) = 0;
};
#endif
