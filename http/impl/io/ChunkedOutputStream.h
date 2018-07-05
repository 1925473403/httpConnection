#include "HttpException.h"
#ifndef CHUNKEDOUTPUTSTREAM_H
#define CHUNKEDOUTPUTSTREAM_H
typedef unsigned char byte;
class ChunkedOutputStream : public OutputStream {
    private:
        SessionOutputBuffer *out;
        byte *cache;
        int cachePosition;
        int cachelen;
        bool wroteLastChunk;
        bool closed;
    protected:
        void flushCache() throw (IOException);
        void flushCacheWithAppend(byte *bufferToAppend, int off, int len) throw (IOException);
        void writeClosingChunk() throw (IOException);
    public:
        ChunkedOutputStream(SessionOutputBuffer *outbuf, int bufferSize);
        ChunkedOutputStream(SessionOutputBuffer *outbuf);
        ~ChunkedOutputStream() { delete[] cache; }
        ChunkedOutputStream(const ChunkedOutputStream &rhs);
        ChunkedOutputStream& operator=(const ChunkedOutputStream &rhs);
        void finish() throw (IOException);
        void write(int b) throw (IOException);
        void write(byte *b, int blen) throw (IOException);
        void write(byte *b, int off, int len) throw (IOException);
        void flush() throw (IOException);
        void close() throw (IOException);
};
#endif
