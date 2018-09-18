#include "HttpException.h"
#ifndef BUFFEREDHTTPENTITY_H
#define BUFFEREDHTTPENTITY_H
typedef unsigned char byte;
class BufferedHttpEntity : public HttpEntityWrapper {
    byte *buffer;
    size_t bufferlen;
    void toByteArray(HttpEntity *entity) ;
    public:
    BufferedHttpEntity(HttpEntity *entity);
    ~BufferedHttpEntity();
    long getContentLength();
    InputStream *getContent() throw(IOException, IllegalStateException);
    bool isChunked();
    bool isRepeatable();
    void writeTo(OutputStream* outstream) throw(IOException);
    bool isStreaming();
};
#endif
