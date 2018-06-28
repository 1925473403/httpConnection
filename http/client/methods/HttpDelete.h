#include "HttpException.h"
#ifndef HTTPDELETE_H
#define HTTPDELETE_H
 class HttpDelete : public HttpEntityEnclosingRequestBase {
     public:
         std::string METHOD_NAME;
         HttpDelete();
         HttpDelete(std::string Uri);
         HttpDelete(URI uri);
         std::string getMethod();
 }
#endif
