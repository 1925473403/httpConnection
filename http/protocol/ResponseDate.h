#include "HttpException.h"
#ifndef RESPONSEDATE_H
#define RESPONSEDATE_H
class ResponseDate : public HttpRequestInterceptor {
    static HttpDateGenerator DATE_GENERATOR ;
    public:
    void process(HttpResponse *response, HttpContext *context) HttpException, IOException;
};
#endif
