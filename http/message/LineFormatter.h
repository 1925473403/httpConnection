#include "HttpException.h"
#include "RefCount.h"
#ifndef LINEFORMATTER_H
#define LINEFORMATTER_H
class LineFormatter:public RefCount {
    public:
        virtual ~LineFormatter() { }
        virtual CharArrayBuffer appendProtocolVersion(CharArrayBuffer&, ProtocolVersion *) = 0;
        virtual CharArrayBuffer formatRequestLine(CharArrayBuffer&, RequestLine*) = 0;
        virtual CharArrayBuffer formatStatusLine(CharArrayBuffer&, StatusLine*) = 0;
        virtual CharArrayBuffer formatHeader(CharArrayBuffer&, Header*) = 0;
};
#endif
