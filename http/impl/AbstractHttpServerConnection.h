#include "HttpException.h"
#ifndef ABSTRACTHTTPSERVERCONNECTION_H
#define ABSTRACTHTTPSERVERCONNECTION_H
class AbstractHttpServerConnection : public HttpServerConnection {
    private:
        EntitySerializer *entityserializer;
        EntityDeserializer *entitydeserializer;
        SessionInputBuffer *inbuffer;
        SessionOutputBuffer *outbuffer;
        HttpMessageParser *requestParser;
        HttpMessageWriter *responseWriter;
    protected:
        void assertOpen() throw(IllegalStateException) = 0;
        EntityDeserializer* createEntityDeserializer();
        EntitySerializer* createEntitySerializer();
        HttpRequestFactory* createHttpRequestFactory();
        HttpMessageParser* createRequestParser(SessionInputBuffer* buffer, HttpRequestFactory* requestFactory, HttpParams *params);
        HttpMessageWriter* createResponseWriter(SessionOutputBuffer *buffer, HttpParams *params);
        void init(SessionInputBuffer* ibuffer, SessionOutputBuffer *obuffer, HttpParams *params);
    public:
        AbstractHttpServerConnection() ;
        virtual ~AbstractHttpServerConnection();
        bool isRequestAvailable(int timeout) throw(IOException);
        void sendResponseHeader(HttpResponse* response) throw (HttpException, IOException);
        void sendResponseEntity(HttpResponse *response) throw (HttpException, IOException);
        void doFlush() throw(IOException);
        void flush() throw(IOException);
        HttpRequest* receiveRequestHeader() throw (HttpException, IOException);
        void receiveRequestEntity(HttpEntityEnclosingRequest *request) throw (HttpException, IOException);
        bool isStale();
};
#endif
