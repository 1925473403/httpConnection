#include "HttpException.h"
#ifndef ABSTRACTSESSIONINPUTBUFFER_H
#define ABSTRACTSESSIONINPUTBUFFER_H
class AbstractSessionInputBuffer : public SessionInputBuffer{
    private:
        InputStream *instream;
        byte *buffer;
        int bytebufferlen;
        int bufferpos;
        int bufferlen;
        ByteArrayBuffer linebuffer;
        bool ascii;
        int maxLineLen;
        int locateLF();
    protected:
        void init(InputStream *ins, int buffersize, HttpParams *params);
    public:
        virtual ~AbstractSessionInputBuffer() { delete [] buffer; }
        int fillBuffer() throw (IOException);
        bool hasBufferedData();
        int read () throw (IOException);
        int read(byte *b, int off, int len) throw (IOException);
        int read(byte *b) throw (IOException);
        int readLine(CharArrayBuffer &charbuffer) throw (IOException);
        int lineFromLineBuffer(CharArrayBuffer &charbuffer) throw (IOException);
        int lineFromReadBuffer(CharArrayBuffer &charbuffer, int pos) throw (IOException);
        std::string readLine() throw (IOExecption);
};
#endif
