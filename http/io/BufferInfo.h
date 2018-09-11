#include "HttpException.h"
#include "RefCount.h"
#ifndef BUFFERINFO_H
#define BUFFERINFO_H
class BufferInfo : virtual public RefCount {
    public:
        virtual ~BufferInfo() { }
        virtual int length() = 0;
        virtual int capacity() = 0;
        virtual int available() = 0;
};
#endif
