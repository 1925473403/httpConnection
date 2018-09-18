#include "HttpException.h"
#ifndef BUFFEREDINPUTSTREAM_H
#define BUFFEREDINPUTSTREAM_H
class ByteArrayInputStream : public InputStream {
    typedef unsigned char byte;
    protected:
        byte *buf;
        int buflen;
        int pos;
        int _mark;
        int count;
    public:
    ByteArrayInputStream(byte *b, int len);
    ByteArrayInputStream(byte *b, int len, int off, int length);
    ~ByteArrayInputStream();
    int read() throw (IOException) ;
    int read(char *b, int blen, int off, int len)throw (IOException) ;
    int read(char *b, int blen, int len) throw (IOException);
    long skip(long n)throw (IOException) ;
    int available()throw (IOException) ;
    bool markSupported();
    void mark(int readAheadLimit);
    void reset();
    void close()throw (IOException) ;
};
#endif
