#include "HttpException.h"
#ifndef HTTPREQUESTRETRYHANDLER_H
#define HTTPREQUESTRETRYHANDLER_H
class HttpRequestRetryHandler {
    public:
        virtual HttpRequestRetryHandler() { }
        virtual bool retryRequest(IOException *exception, int executionCount, HttpContext* context) = 0;
};
#endif
