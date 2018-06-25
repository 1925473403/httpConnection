#include "HttpException.h"
#ifdef HTTPRESPONSEINTERCEPTOR_H
#define HTTPRESPONSEINTERCEPTOR_H
class HttpResponseInterceptor {
    public:
    virtual ~HttpResponseInterceptor () { }
    virtual void process(HttpResponse *request, HttpContext *context) throw(HttpException, IOException) = 0;
};
#endif
