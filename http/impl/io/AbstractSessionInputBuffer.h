#include "HttpException.h"
#ifndef ABSTRACTSESSIONINPUTBUFFER_H
#define ABSTRACTSESSIONINPUTBUFFER_H
class AbstractSessionInputBuffer : public SessionInputBuffer, public BufferInfo {
    private:
        InputStream *instream;
        byte *buffer;
        int bufferpos;
        int bufferlen;
        ByteArrayBuffer linebuffer;
        CharBuffer cbuf;
        bool ascii;
        int maxLineLen;
        int minChunkLimit;
        CodingErrorAction *onMalformedInputAction;
        CodingErrorAction *onUnMappableInputAction;
        int locateLF();
        int appendDecoded(CharArrayBuffer &charbuffer, ByteBuffer &bbuf) throw (IOException);
        int handleDecodingResult(CoderResult *result, CharArrayBuffer &charbuffer, ByteBuffer &bbuf) throw (IOException);
    protected:
        void init(InputStream *ins, int buffersize, HttpParams *params);
    public:
        int capacity() ;
        int length();
        int available();
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
