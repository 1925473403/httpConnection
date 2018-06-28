#include "HttpException.h"
#ifndef HTTPURIREQUEST_H
#define HTTPURIREQUEST_H
class HttpUriRequest : public HttpRequest {
    public:
        virtual ~HttpUriRequest() { }
        virtual std::string getMethod() = 0;
        virtual URI getURI() = 0;
        virtual void abort() = 0;
        bool isAborted() = 0;
};
#endif
