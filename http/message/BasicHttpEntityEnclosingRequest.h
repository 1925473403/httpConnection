#include "HttpException.h"
#ifndef BASICHTTPENTITYENCLOSINGREQUST_H
#define BASICHTTPENTITYENCLOSINGREQUST_H
class BasicHttpEntityEnclosingRequest :public BasicHttpRequest , public HttpEntityEnclosingRequest {
    private:
        HttpEntity *entity;
    public:
        BasicHttpEntityEnclosingRequest(std::string method, std::string uri);
        BasicHttpEntityEnclosingRequest(std::string method, std::string uri, ProtocolVersion *ver);
        BasicHttpEntityEnclosingRequest(RequestLine *requestline);
        HttpEntity* getEntity();
        void setEntity(HttpEntity* e);
        bool expectContinue();
};
#endif
