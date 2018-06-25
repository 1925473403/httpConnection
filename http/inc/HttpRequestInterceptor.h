#include "HttpException.h"
#ifdef HTTPREQUESTINTERCEPTOR_H
#define HTTPREQUESTINTERCEPTOR_H
class HttpRequestInterceptor {
    public:
    virtual ~HttpRequestInterceptor () { }
    virtual void process(HttpRequest *request, HttpContext *context) throw(HttpException, IOException) = 0;
};
#endif
