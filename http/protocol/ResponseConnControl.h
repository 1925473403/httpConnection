#include "HttpException.h"
#ifndef RESPONSECONNCONTROL_H
#define RESPONSECONNCONTROL_H
class ResponseConnControl : public HttpResponseInterceptor {
    public:
        ResponseConnControl() { }
        ~ResponseConnControl() { }
        void process(HttpResponse *response, HttpContext *context) throw (HttpException, IOException);
};
#endif
