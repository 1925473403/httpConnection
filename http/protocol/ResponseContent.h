#include "HttpException.h"
#ifndef RESPONSECONTENT_H
#define RESPONSECONTENT_H
class ResponseContent : public HttpRequestInterceptor {
    public:
    void process(HttpResponse *response, HttpContext *context) throw (HttpException, IOException);
};
#endif
