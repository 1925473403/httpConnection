#include "HttpException.h"
#ifndef ABSTRACTHTTPCLIENTCONNECTION_H
#define ABSTRACTHTTPCLIENTCONNECTION_H
class AbstractHttpClientConnection : public HttpClientConnection {
    private:
        EntitySerializer *entityserializer;
        EntityDeserializer *entitydeserializer;
        SessionInputBuffer *inbuffer;
        SessionOutputBuffer *outbuffer;
        HttpMessageParser *responseParser;
        HttpMessageWriter *requestWriter;
    protected:
        void assertOpen() throw(IllegalStateException) = 0;
        EntityDeserializer* createEntityDeserializer();
        EntitySerializer* createEntitySerializer();
        HttpResponseFactory* createHttpResponseFactory();
        HttpMessageParser* createResponseParser(SessionInputBuffer* buffer, HttpResponseFactory* responseFactory, HttpParams *params);
        HttpMessageWriter* createRequestWriter(SessionOutputBuffer *buffer, HttpParams *params);
        void init(SessionInputBuffer* ibuffer, SessionOutputBuffer *obuffer, HttpParams *params);
    public:
        AbstractHttpClientConnection() ;
        virtual ~AbstractHttpClientConnection();
        bool isResponseAvailable(int timeout) throw(IOException);
        void sendRequestHeader(HttpRequest* request) throw (HttpException, IOException);
        void sendRequestEntity(HttpEntityEnclosingRequest* request) throw (HttpException, IOException);
        void doFlush() throw(IOException);
        void flush() throw(IOException);
        HttpResponse* receiveResponseHeader() throw (HttpException, IOException);
        void receiveResponseEntity(HttpResponse *response) throw (HttpException, IOException);
        bool isStale();
};
#endif
