#include "HttpException.h"
#ifndef CONTENTLENGTHOUTPUTSTREAM_H
#define CONTENTLENGTHOUTPUTSTREAM_H
class ContentLengthOutputStream : public OutputStream {
    private:
        SessionOutputBuffer *out;
        long contentLength;
        long total;
        bool closed;
    public:
        ContentLengthOutputStream(SessionOutputBuffer *outbuf, long contentlen);
        ContentLengthOutputStream(const ContentLengthOutputStream &rhs);
        ContentLengthOutputStream& operator=(const ContentLengthOutputStream &rhs);
        void close() throw (IOException);
        void flush() throw (IOException);
        void write(byte *b, int blen, int off, int len) throw (IOException);
        void write(byte *b, int blen) throw (IOException);
        void write(int b) throw (IOException);
};
#endif
