#include "HttpException.h"
#ifndef IDENTITYOUTPUTSTREAM_H
#define IDENTITYOUTPUTSTREAM_H
typedef unsigned char byte;
class IdentityOutputStream : public OutputStream {
    private:
        SessionOutputBuffer *out;
        bool closed;
    public:
        IdentityOutputStream(SessionOutputBuffer *outbuf);
        void close() throw (IOException);
        void flush() throw (IOException);
        void write(byte *b, int blen, int off, int len) throw (IOException);
        void write(byte *b, int blen) throw (IOException);
        void write(int b) throw (IOException);
};
#endif
