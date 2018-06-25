#include "HttpException.h"
#ifndef CHARARRAYBUFFER_H
#define CHARARRAYBUFFER_H
class ByteArrayBuffer;
class CharArrayBuffer {
    typedef char byte;
    char *_buffer;
    long _capacity;
    long len;
    void expand(int newlen) ;

    public:
        CharArrayBuffer(int c) ;
        ~CharArrayBuffer() { delete[] _buffer; }
        CharArrayBuffer(const CharArrayBuffer& rhs) ;
        CharArrayBuffer& operator=(const CharArrayBuffer& rhs) ;
        void append(char *b, int off, int l) ;
        void append(std::string &s) ;
        void append(CharArrayBuffer &b) ;
        void append(const char *s);
        void append(char ch) ;
        void append(int l) ;
        void append(float f) ;
        void append(ByteArrayBuffer &b, int off, int l) ;
        void clear() ;
        char *buffer() ;
        std::string toString() ;
        char charAt(int i) ;
        void ensureCapacity(int required) ;
        char *toCharArray() ;
        void setLength(int l) ;
        long capacity() const { return _capacity; }
        long length() const { return len; }
        char* buffer() const { return _buffer; }
        bool isEmpty() const { return len == 0; }
        bool isFull() const { return len == _capacity; }
        int indexOf(int ch, int beginIndex, int endIndex);
        int indexOf(int ch);
        std::string substring(int beginIndex, int endIndex);
        std::string substringTrimmed(int beginIndex, int endIndex);
};
#endif
