#include "HttpException.h"
#ifndef REQUESTCONNCONTROL_H
#define REQUESTCONNCONTROL_H
class RequestConnControl : public HttpRequestInterceptor {
    public :
        RequestConnControl() { }
        ~RequestConnControl() { }
        void process(HttpRequest *request, HttpContext *context) throw (HttpException, IOException);
};
#endif
