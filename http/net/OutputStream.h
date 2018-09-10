#include "HttpException.h"
#ifndef OUTPUTSTREAM_H
#define OUTPUTSTREAM_H
class OutputStream {
    public:
    virtual ~OutputStream() { }
    virtual int write(char *b, int blen, int len) throw (IOException) = 0;
    virtual int write(char *b, int blen, int off, int len) throw (IOException) = 0;
    virtual int write(int b) throw (IOException) = 0;
    virtual void close() throw (IOException) = 0;
};
#endif
