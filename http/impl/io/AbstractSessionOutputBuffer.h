#include "HttpException.h"
#ifndef ABSTRACTSESSIONOUTPUTBUFFER_H
#define ABSTRACTSESSIONOUTPUTBUFFER_H
class AbstractSessionOutputBuffer : public SessionOutputBuffer, public BufferInfo {
    private:
        static char CLRF[2];
        static int MAX_CHUNK;
        OutputStream *outstream;
        ByteArrayBuffer buffer;
        bool ascii;
    protected:
    public:
        virtual ~AbstractSessionOutputBuffer() { }
        void init(OutputStream *oustream, int buffersize, HttpParams *params);
        int capacity();
        int length();
        int available();
        void flushBuffer () throw (IOException);
        void flush() throw(IOException);
        void write(byte *b, int off, int len) throw (IOException);
        void write(byte *b, int) throw (IOException);
        void write(int b) throw (IOException);
        void writeLine(std::string s) throw (IOException);
        void writeLine(CharArrayBuffer &charbuffer) throw (IOException);
};
#endif
