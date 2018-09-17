#include "HttpException.h"
#include "RefCount.h"
#ifndef HTTPENTITY_H
#define HTTPENTITY_H
class HttpEntity : public RefCount {
    public:
        virtual ~HttpEntity() { }
        virtual bool isRepeatable() = 0;
        virtual bool isChunked() = 0;
        virtual long getContentLength() = 0;
        virtual Header* getContentType() = 0;
        virtual Header* getContentEncoding() = 0;
        virtual void writeTo(OutputStream *outstream) throw (IOException) = 0;
        virtual bool isStreaming() = 0;
        virtual InputStream* getContent() throw (IOException, IllegalStateException) = 0;
        virtual void consumeContent() throw (IOException) = 0;
};
#endif
