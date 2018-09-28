#include "HttpException.h"
#include "RefCount.h"
#ifndef HTTPREQUESTEXECUTOR_H
#define HTTPREQUESTEXECUTOR_H
class HttpRequestExecutor : public RefCount {
    private:
    public:
        HttpRequestExecutor() { }
        virtual ~HttpRequestExecutor() { }
        bool canResponseHaveBody(HttpRequest *request, HttpResponse *response) ;
        HttpResponse* execute(HttpRequest* request, HttpClientConnection* conn, HttpContext* context) throw (IOException, HttpException) ;
        void preProcess(HttpRequest* request, HttpProcessor* processor, HttpContext* context)  throw (IOException, HttpException) ;
        HttpResponse* doSendRequest(HttpRequest* request, HttpClientConnection* conn, HttpContext* context) throw (IOException, HttpException) ;
        HttpResponse* doReceiveResponse(HttpRequest *request, HttpClientConnection* conn, HttpContext* context) throw (IOException, HttpException) ;
        void postProcess(HttpResponse *response, HttpProcessor* processor, HttpContext* context)  throw (IOException, HttpException) ;
};
#endif
