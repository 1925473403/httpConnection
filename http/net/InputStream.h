#include "HttpException.h"
#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H
class InputStream {
    public:
    virtual ~InputStream() { }
    virtual int read(char *b, int blen, int len) throw (IOException) = 0;
    virtual int read(char *b, int blen, int off, int len) throw (IOException) = 0;
    virtual int read() throw (IOException) = 0;
    virtual long skip(long numbytes) throw (IOException) = 0;
    virtual int available() throw (IOException) = 0;
    virtual void close() throw (IOException) =0 ;
};
#endif
