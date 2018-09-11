#include "HttpException.h"
#ifndef BASICLINEPARSER_H
#define BASICLINEPARSER_H
class BasicLineParser  : public LineParser {
    protected:
        ProtocolVersion *protocol;
        ProtocolVersion* createProtocolVersion(int major, int minor);
        RequestLine* createRequestLine(std::string method, std::string uri, ProtocolVersion *ver);
        StatusLine* createStatusLine(ProtocolVersion *ver, int status, std::string reason);
        void skipWhitespace(CharArrayBuffer &buffer, ParserCursor *cursor);
    public:
        ~BasicLineParser() { }
        static BasicLineParser DEFAULT;
        BasicLineParser(ProtocolVersion *proto);
        BasicLineParser();
        static ProtocolVersion* parseProtocolVersion(std::string value, LineParser *parser) throw (ParseException);
        ProtocolVersion* parseProtocolVersion(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException);
        bool hasProtocolVersion(CharArrayBuffer &buffer, ParserCursor *cursor);
        static RequestLine* parseRequestLine(std::string value, LineParser *parser) throw (ParseException);
        RequestLine* parseRequestLine(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException);
        static StatusLine* parseStatusLine(std::string value, LineParser *parser) throw (ParseException);
        StatusLine* parseStatusLine(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException);
        static Header* parseHeader(std::string value, LineParser *parser) throw (ParseException);
        Header* parseHeader(CharArrayBuffer &buffer) throw (ParseException);
};
#endif
