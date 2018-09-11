#include "HttpException.h"
#include "RefCount.h"
#ifndef SESSIONINPUTBUFFER_H
#define SESSIONINPUTBUFFER_H
class SessionInputBuffer: public RefCount {
    public:
        virtual ~SessionInputBuffer() { }
        virtual int read(char *b, int blen, int off, int len) throw(IOException) = 0;
        virtual int read(char *b, int blen) throw(IOException) = 0;
        virtual int read() throw(IOException) = 0;
        virtual int readLine(CharArrayBuffer &buffer) throw(IOException) = 0;
        virtual std::string readLine() throw(IOException) = 0;
        virtual bool isDataAvailable(int timeout) throw(IOException) = 0;
};
#endif
