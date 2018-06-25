#include "HttpException.h"
#ifndef BASICHTTPMESSAGE_H
#define BASICHTTPMESSAGE_H
class BasicHttpRequest : public AbstractHttpMessage, public HttpRequest {
    public:
        BasicHttpRequest(std::string m, std::string u) ;
        BasicHttpRequest(std::string m, std::string u, ProtocolVersion*);
        BasicHttpRequest(RequestLine *);
        ProtocolVersion *getProtocolVersion();
        RequestLine *getRequestLine();
    private:
        RequestLine *requestline;
        std::string method;
        std::string uri;
};
#endif
