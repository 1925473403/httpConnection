#include "HttpException.h"
#ifndef HTTPENTITYENCLOSINGREQUESTBASE_H
#define HTTPENTITYENCLOSINGREQUESTBASE_H
class HttpEntityEnclosingRequestBase : public HttpRequestBase, public HttpEntityEnclosingRequest {
    private:
        HttpEntity* entity;
    public:
        HttpEntityEnclosingRequestBase();
        HttpEntity* getEntity();
        void setEntity(HttpEntity *e);
        bool expectContinue();
};
#endif
