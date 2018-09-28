#include "HttpException.h"
#ifndef HTTPPROCESSOR_H
#define HTTPPROCESSOR_H
class HttpRequestInterceptor;
class HttpResponseInterceptor;
class HttpProcessor : public HttpRequestInterceptor, public HttpResponseInterceptor {
    public:
    using HttpRequestInterceptor::process;
    using HttpResponseInterceptor::process;
    virtual ~HttpProcessor() { }
};
#endif
