#include "HttpException.h"
#include "RefCount.h"
#ifndef HTTPREQUESTINTERCEPTOR_H
#define HTTPREQUESTINTERCEPTOR_H
class HttpRequestInterceptor : public virtual RefCount {
    public:
    virtual ~HttpRequestInterceptor () { }
    virtual void process(HttpRequest *request, HttpContext *context) throw(HttpException, IOException) = 0;
};
#endif
