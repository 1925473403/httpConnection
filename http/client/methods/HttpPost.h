#include "HttpException.h"
#ifndef HTTPPOST_H
#define HTTPPOST_H
 class HttpPost : public HttpEntityEnclosingRequestBase {
     public:
         std::string METHOD_NAME;
         HttpPost();
         HttpPost(std::string Uri);
         HttpPost(URI uri);
         std::string getMethod();
 }
#endif
