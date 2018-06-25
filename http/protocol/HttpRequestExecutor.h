#include "HttpException.h"
#ifndef HTTPREQUESTEXECUTOR_H
#define HTTPREQUESTEXECUTOR_H
class HttpRequestExecutor {
    private:
    public:
        HttpRequestExecutor() { }
        ~HttpRequestExecutor() { }
        bool canResponseHaveBody(HttpRequest *request, HttpResponse *response) ;
        HttpResponse* execute(HttpRequest* request, HttpClientConnection* conn, HttpContext* context) throws IOException, HttpException ;
        void preProcess(HttpRequest* request, HttpProcessor* processor, HttpContext* context) throws HttpException, IOException ;
        HttpResponse* doSendRequest(HttpRequest* request, HttpClientConnection* conn, HttpContext* context) throws IOException, HttpException ;
        HttpResponse* doReceiveResponse(HttpRequest *request, HttpClientConnection* conn, HttpContext* context) throws IOException, HttpException ;
        void postProcess(HttpRequest* request, HttpProcessor* processor, HttpContext* context) throws HttpException, IOException ;
};
#endif
