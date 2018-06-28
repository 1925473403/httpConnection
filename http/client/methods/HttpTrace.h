#include "HttpException.h"
#ifndef HTTPTRACE_H
#define HTTPTRACE_H
 class HttpTrace : public HttpEntityEnclosingRequestBase {
     public:
         std::string METHOD_NAME;
         HttpTrace();
         HttpTrace(std::string Uri);
         HttpTrace(URI uri);
         std::string getMethod();
 }
#endif
