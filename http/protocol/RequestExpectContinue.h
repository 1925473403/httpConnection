#include "HttpException.h"
#ifndef REQUESTEXPECTCONTINUE_H
#define REQUESTEXPECTCONTINUE_H
class RequestExpectContinue : public HttpRequestInterceptor {
    public :
        RequestExpectContinue() { }
        ~RequestExpectContinue() { }
        void process(HttpRequest *request, HttpContext *context) throw (HttpException, IOException);
};
#endif
