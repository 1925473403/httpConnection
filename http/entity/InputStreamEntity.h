#include "HttpException.h"
#ifndef INPUTSTREAMENTITY_H
#define INPUTSTREAMENTITY_H
class InputStreamEntity : public AbstractHttpEntity {
    typedef unsigned char byte;
    static int BUFFER_SIZE;
    InputStream *content;
    long length;
    bool consumed;
    public:
    InputStreamEntity(InputStream *instream, long len);
    ~InputStreamEntity();
    bool isRepeatable() { return false; }
    long getContentLength() { return length; }
    InputStream* getContent() throw(IOException, IllegalStateException);
    void writeTo(OutputStream *outstream) throw(IOException) ;
    bool isStreaming();
    void consumeContent() throw(IOException);
};
#endif
