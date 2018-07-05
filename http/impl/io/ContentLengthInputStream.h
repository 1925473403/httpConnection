#include "HttpException.h"
#ifndef CONTENTLENGTHINPUTSTREAM_H
#define CONTENTLENGTHINPUTSTREAM_H
class ContentLengthInputStream : public InputStream {
    private:
        static int BUFFER_SIZE;
        long contentLength;
        long pos;
        bool closed;
        SessionInputBuffer *in;
    public:
        ContentLengthInputStream(SessionInputBuffer *inbuf, long contentLength);
        void close() throw (IOException);
        int read() throw (IOException);
        int read (byte *b, int blen, int off, int len) throw (IOException);
        int read(byte *b, int blen) throw (IOException);
        long skip(long n) throw (IOException);
};
#endif
