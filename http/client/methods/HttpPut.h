#include "HttpException.h"
#ifndef HTTPPUT_H
#define HTTPPUT_H
 class HttpPut : public HttpEntityEnclosingRequestBase {
     public:
         std::string METHOD_NAME;
         HttpPut();
         HttpPut(std::string Uri);
         HttpPut(URI uri);
         std::string getMethod();
 }
#endif
