#include "HttpException.h"
#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H
class HttpClient {
    public:
        virtual HttpClient() { }
        virtual HttpParams* getParams() = 0;
        virtual ClientConnectionManager* getConnectionManager() = 0;
        virtual HttpResponse* execute(HttpUriRequest* request) throw (IOException, ClientProtocolException) = 0;
        virtual HttpResponse* execute(HttpUriRequest* request, HttpContext *context) throw (IOException, ClientProtocolException) = 0;
        virtual HttpResponse* execute(HttpHost* target, HttpRequest *request) throw (IOException, ClientProtocolException) = 0;
        virtual HttpResponse* execute(HttpHost* target, HttpRequest *request, HttpContext *context) throw (IOException, ClientProtocolException) = 0;
};
#endif
