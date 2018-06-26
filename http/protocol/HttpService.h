#include "HttpException.h"
#ifndef HTTPSERVICE_H
#define HTTPSERVICE_H
class HttpService {
    private:
        HttpParams *params;
        HttpProcessor *processor;
        HttpRequestHandlerResolver *handlerResolver;
        ConnectionReuseStrategy *connStrategy;
        HttpResponseFactory *responseFactory;
        HttpExpectationVerifier *expectationVerifier;
    protected:
        void doService(HttpRequest *request, HttpResponse *response, HttpContext *context) throw(HttpException, IOException);
    public:
        HttpService(HttpProcessor *p, ConnectionReuseStrategy *c, HttpResponseFactory *r);
        void setHttpProcessor(HttpProcessor *p);
        void setConnReuseStrategy(ConnectionReuseStrategy *c);
        void setResponseFactory(HttpResponseFactory *r);
        void setHandlerResolver(HttpRequestHandlerResolver *h);
        void setExpectationVerifier(HttpExpectationVerifier *e);
        HttpParams *getParams();
        void setParams(HttpParams *p);
        void handleRequest(HttpServerConnection *conn, HttpContext *context) throw(IOException, HttpException);
        void handleException(HttpException *ex, HttpResponse *response);
};
#endif
