#include "HttpException.h"
#ifndef HTTPHEAD_H
#define HTTPHEAD_H
 class HttpHead : public HttpEntityEnclosingRequestBase {
     public:
         std::string METHOD_NAME;
         HttpHead();
         HttpHead(std::string Uri);
         HttpHead(URI uri);
         std::string getMethod();
 }
#endif
