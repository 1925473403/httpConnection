#include "HttpException.h"
#include "RefCount.h"
#ifndef HTTPEXPECTATIONVERIFIER_H
#define HTTPEXPECTATIONVERIFIER_H
class HttpExpectationVerifier : public RefCount {
    public:
        virtual ~HttpExpectationVerifier () { }
        virtual void verify(HttpRequest *request, HttpResponse *response, HttpContext *context) throw(HttpException) = 0;
};
#endif
