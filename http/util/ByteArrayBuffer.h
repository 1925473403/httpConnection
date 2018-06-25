#include "HttpException.h"
#ifndef BYTEARRAYBUFFER_H
#define BYTEARRAYBUFFER_H
class CharArrayBuffer;
class ByteArrayBuffer {
    typedef unsigned char byte;
    byte *_buffer;
    long _capacity;
    long len;
    void expand(int newlen) ;
    public:
        ByteArrayBuffer(int c) ;
        ~ByteArrayBuffer() { delete[] _buffer; }
        ByteArrayBuffer(const ByteArrayBuffer& rhs) ;
        ByteArrayBuffer& operator=(const ByteArrayBuffer& rhs) ;
        void append(byte *b, int off, int l) ;
        void append(std::string &s) ;
        void append(ByteArrayBuffer &b) ;
        void append(char ch); 
        void append(int l) ;
        void append(float f) ;
        void append(CharArrayBuffer &b, int off, int l) ;
        void clear() ;
        long capacity() const { return _capacity; }
        long length() const { return len; }
        byte *buffer() const { return _buffer; }
        std::string toString() ;
        byte byteAt(int i) ;
        void ensureCapacity(int required) ;
        byte* toByteArray() ;
        void setLength(int l) ;
        bool isEmpty() const { return len == 0; }
        bool isFull() const { return len == _capacity; }
};
#endif
