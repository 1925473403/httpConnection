#include "HttpException.h"
#ifndef REQUESTDATE_H
#define REQUESTDATE_H
class RequestDate : public HttpRequestInterceptor {
    static HttpDateGenerator DATE_GENERATOR ;
    public:
    void process(HttpRequest *request, HttpContext *context) HttpException, IOException;
};
#endif
