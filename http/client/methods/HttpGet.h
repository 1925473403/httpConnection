#include "HttpException.h"
#ifndef HTTPGET_H
#define HTTPGET_H
 class HttpGet : public HttpEntityEnclosingRequestBase {
     public:
         std::string METHOD_NAME;
         HttpGet();
         HttpGet(std::string Uri);
         HttpGet(URI uri);
         std::string getMethod();
 }
#endif
