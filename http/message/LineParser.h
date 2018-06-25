#include "HttpException.h"
#ifndef LINEPARSER_H
#define LINEPARSER_H
class LineParser {
    public:
        virtual ~LineParser() { }
        virtual ProtocolVersion *parseProtocolVersion(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException) = 0;
        virtual bool hasProtocolVersion(CharArrayBuffer &buffer, ParserCursor *cursor);
        virtual RequestLine* parseRequestLine(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException) = 0;
        virtual StatusLine* parseStatusLine(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException) = 0;
        virtual Header* parseHeader(CharArrayBuffer &buffer) throw (ParseException) = 0;
};
#endif
