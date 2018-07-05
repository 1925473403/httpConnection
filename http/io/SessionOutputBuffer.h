#include "HttpException.h"
#ifndef SESSIONOUTPUTBUFFER_H
#define SESSIONOUTPUTBUFFER_H
class SessionOutputBuffer {
    public:
        virtual ~SessionOutputBuffer() { }
        virtual write(char *b, int blen, int off, int len) throw(IOException) = 0;
        virtual write(char *b, int blen) throw(IOException) = 0;
        virtual write(int b) throw(IOException) = 0;
        virtual void writeLine(std::string &) throw(IOException) = 0;
        virtual void writeLine(CharArrayBuffer &) throw(IOException) = 0;
        virtual void flush() throw(IOException) = 0;
};
#endif
