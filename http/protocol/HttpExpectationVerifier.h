#include "HttpException.h"
#ifndef HTTPEXPECTATIONVERIFIER_H
#define HTTPEXPECTATIONVERIFIER_H
class HttpExpectationVerifier {
    public:
        virtual HttpExpectationVerifier () { }
        void verify(HttpRequest *request, HttpResponse *response, HttpContext *context) throw(HttpException) = 0;
};
#endif
