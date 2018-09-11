#include "HttpException.h"
#include "RefCount.h"
#ifndef LINEPARSER_H
#define LINEPARSER_H
class LineParser : public RefCount {
    public:
        virtual ~LineParser() { }
        virtual ProtocolVersion *parseProtocolVersion(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException) = 0;
        virtual bool hasProtocolVersion(CharArrayBuffer &buffer, ParserCursor *cursor) = 0;
        virtual RequestLine* parseRequestLine(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException) = 0;
        virtual StatusLine* parseStatusLine(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException) = 0;
        virtual Header* parseHeader(CharArrayBuffer &buffer) throw (ParseException) = 0;
};
#endif
