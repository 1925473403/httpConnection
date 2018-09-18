#include "HttpException.h"
#ifndef HTTPENTITYWRAPPER_H
#define HTTPENTITYWRAPPER_H
class HttpEntityWrapper : public HttpEntity {
    protected:
        HttpEntity *wrappedEntity;
    public:
        HttpEntityWrapper(HttpEntity *);
        ~HttpEntityWrapper();
        bool isRepeatable();
        bool isChunked();
        long getContentLength();
        Header* getContentType();
        Header* getContentEncoding();
        InputStream* getContent() throw (IOException, IllegalStateException);
        void writeTo(OutputStream *outstream) throw (IOException);
        bool isStreaming();
        void consumeContent() throw(IOException);
};
#endif
