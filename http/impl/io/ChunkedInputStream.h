#include "HttpException.h"
#ifndef CHUNKEDINPUTSTREAM_H
#define CHUNKEDINPUTSTREAM_H
class ChunkedInputStream : public InputStream {
    private:
        SessionInputBuffer *in;
        CharArrayBuffer buffer;
        int chunkSize;
        int pos;
        bool bof;
        bool eof;
        bool closed;
        vector<Header *> footers;
        void nextChunk() throw (IOException);
        int getChunkSize() throw (IOException);
        void parseTrailerHeaders() throw (IOException);
    public:
        ChunkedInputStream(SessionInputBuffer *inbuf);
        int read() throw (IOException);
        int read (byte *b, int blen, int off, int len) throw (IOException);
        int read(byte *b, int blen) throw (IOException);
        void close() throw (IOException);
        void getFooters(vector<Header *> &res);
        static void exhaustInputStream(InputStream *inStream) throw (IOException);
};
#endif
