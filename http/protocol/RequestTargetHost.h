#include "HttpException.h"
#ifndef REQUESTTARGETHOST_H
#define REQUESTTARGETHOST_H
class RequestTargetHost : public HttpRequestInterceptor {
    public:
        RequestTargetHost () { }
        ~RequestTargetHost () { }
        void process(HttpRequest *request, HttpContext *context) throw (HttpException, IOException);
};
#endif
