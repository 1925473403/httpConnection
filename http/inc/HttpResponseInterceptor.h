#include "HttpException.h"
#include "RefCount.h"
#ifndef HTTPRESPONSEINTERCEPTOR_H
#define HTTPRESPONSEINTERCEPTOR_H
class HttpResponseInterceptor : public RefCount {
    public:
    virtual ~HttpResponseInterceptor () { }
    virtual void process(HttpResponse *, HttpContext *) throw(HttpException, IOException) = 0;
};
#endif
