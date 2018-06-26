#include "HttpException.h"
#ifndef REQUESTUSERAGENT_H
#define REQUESTUSERAGENT_H
class RequestUserAgent : public HttpRequestInterceptor {
    public:
        RequestUserAgent() { }
        ~RequestUserAgent() { }
        void process(HttpRequest* request, HttpContext *context) throw (HttpException, IOException);
};
#endif
