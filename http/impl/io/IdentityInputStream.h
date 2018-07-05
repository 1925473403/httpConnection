#include "HttpException.h"
#ifndef IDENTITYINPUTSTREAM_H
#define IDENTITYINPUTSTREAM_H
class IdentityInputStream : public InputStream {
    private:
        SessionInputBuffer *in;
        bool closed;
    public:
        IdentityInputStream(SessionInputBuffer *inbuf);
        int available() throw(IOException);
        void close() throw(IOException);
        int read() throw(IOException);
        int read(byte *b, int blen, int off, int len) throw(IOException);
};
#endif
