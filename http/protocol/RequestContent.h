#include "HttpException.h"
#ifndef REQUESTCONTENT_H
#define REQUESTCONTENT_H
class RequestContent : public HttpRequestInterceptor {
    public:
    void process(HttpRequest *request, HttpContext *context) throw (HttpException, IOException);
};
#endif
