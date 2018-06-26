#include "HttpException.h"
#ifndef HTTPCLIENTCONNECTION_H 
#define HTTPCLIENTCONNECTION_H
class HttpClientConnection : public HttpConnection {
    public:
        virtual ~HttpConnection() { }
        virtual bool isResponseAvailable(int timeout) throw (IOException) = 0;
        virtual void sendRequestHeader(HttpRequest request) throw (HttpException, IOException) = 0;
        virtual void sendRequestEntity(HttpEntityEnclosingRequest request) throw (HttpException, IOException) = 0;
        virtual HttpResponse receiveResponseHeader() throw (HttpException, IOException) = 0;
        virtual void receiveResponseEntity(HttpResponse response) throw (HttpException, IOException) = 0;
        virtual void flush() throw (IOException) = 0;
};
#endif
