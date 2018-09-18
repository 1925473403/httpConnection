#include "HttpException.h"
#ifndef BYTEARRAYENTITY_H
#define BYTEARRAYENTITY_H
class ByteArrayEntity : public AbstractHttpEntity {
    typedef unsigned char byte;
    protected:
    byte *content;
    int contentlen;
    public:
    ByteArrayEntity(byte *b, int blen);
    bool isRepeatable() { return true; }
    long getContentLength() { return contentlen; }
    InputStream* getContent() throw (IOException, IllegalStateException) ;
    void writeTo(OutputStream *outstream) throw (IOException);
    bool isStreaming() { return false; }
};
#endif
