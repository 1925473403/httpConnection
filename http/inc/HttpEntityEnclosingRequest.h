#include "HttpException.h"
#ifndef HTTPENTITYENCLOSINGREQUEST_H
#define HTTPENTITYENCLOSINGREQUEST_H
class HttpEntityEnclosingRequest  : public HttpRequest {
    public:
    virtual ~HttpEntityEnclosingRequest() { }
    virtual bool expectContinue() = 0;
    virtual void setEntity(HttpEntity* entity) = 0;
    virtual HttpEntity* getEntity() = 0;
};
#endif
