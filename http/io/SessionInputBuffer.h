#include "HttpException.h"
#ifndef SESSIONINPUTBUFFER_H
#define SESSIONINPUTBUFFER_H
class SessionInputBuffer {
    public:
        virtual ~SessionInputBuffer() = 0;
        virtual int read(char *b, int off = 0, int len = 0) throws IOException = 0;
        virtual int read() throws IOException = 0;
        virtual int readLine(CharArrayBuffer &buffer) throws IOException = 0;
        virtual std::string readLine() throws IOException = 0;
        virtual bool isDataAvailable(int timeout) throws IOException = 0;
};
#endif
