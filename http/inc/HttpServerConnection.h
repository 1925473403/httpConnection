#include "HttpException.h"
#ifndef HTTPSERVERCONNECTION_H
#define HTTPSERVERCONNECTION_H
class HttpServerConnection : public HttpConnection {
    public:
        virtual ~HttpServerConnection() { }
        virtual HttpRequest* receiveRequestHeader() throw (HttpException, IOException) = 0;
        virtual void receiveRequestEntity(HttpEntityEnclosingRequest* request) throw(HttpException, IOException) = 0;
        virtual void sendResponseHeader(HttpResponse* response) throw(HttpException, IOException) = 0;
        virtual void sendResponseEntity(HttpResponse* response) throw(HttpException, IOException) = 0;
        virtual void flush() throw(IOException) = 0;
};
#endif
