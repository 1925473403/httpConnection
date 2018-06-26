#include "HttpException.h"
#ifndef HTTPPROCESSOR_H
#define HTTPPROCESSOR_H
class HttpProcessor : public HttpRequestInterceptor, public HttpResponseInterceptor {
    public:
    virtual HttpProcessor() { }
};
#endif
