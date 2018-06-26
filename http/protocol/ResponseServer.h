#include "HttpException.h"
#ifndef RESPONSESERVER_H
#define RESPONSESERVER_H
class ResponseServer : public HttpResponseInterceptor {
    public :
        ResponseServer() { }
        ~ResponseServer() { }
        void process(HttpResponse *response, HttpContext *context) throw (HttpException, IOException);
};
#endif
