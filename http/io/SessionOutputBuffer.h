#include "HttpException.h"
#ifndef SESSIONOUTPUTBUFFER_H
#define SESSIONOUTPUTBUFFER_H
class SessionOutputBuffer {
    public:
        virtual write(char *b, int off = 0, int len = 0) throws IOException = 0;
        virtual write(int b) throws IOException = 0;
        virtual void writeLine(std::string &) throws IOException = 0;
        virtual void writeLine(CharArrayBuffer &) throws IOException = 0;
        virtual void flush() throws IOException = 0;
};
#endif
