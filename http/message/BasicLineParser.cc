#include "HttpException.h"
#ifndef BASICLINEPARSER_H
#include "BasicLineParser.h"
#endif
BasicLineParser BasicLineParser::DEFAULT;
ProtocolVersion* createProtocolVersion(int major, int minor) {
    return protocol->forVersion(major, minor);
}
RequestLine* createRequestLine(std::string method, std::string uri, ProtocolVersion *ver) {
    return new BasicRequestLine(method, uri, ver);
}
StatusLine* createStatusLine(ProtocolVersion *ver, int status, std::string reason) {
    return new BasicStatusLine(ver, status, reason);
}
void skipWhitespace(CharArrayBuffer &buffer, ParserCursor *cursor) {
    int pos = cursor->getPos();
    int indexTo = cursor->getUpperBound();
    while ((pos < indexTo) && HTTP::isWhitespace(buffer.charAt(pos))) pos++;
    cursor->updatePos(pos);
}
BasicLineParser(ProtocolVersion *proto) : protocol(proto) {
    if (proto == NULL) protocol = HttpVersion::HTTP_1_1;
}
BasicLineParser() {
    protocol = HttpVersion::HTTP_1_1;
}
ProtocolVersion* parseProtocolVersion(std::string value, LineParser *parser) throw (ParseException) {
    if (value.length() == 0) throw IllegalArgumentException ("Value to parse may not be null.");
    if (parser == NULL) parser = &(BasicLineParser::DEFAULT);
    CharArrayBuffer buffer(value.length());
    buffer.append(value);
    ParserCursor cursor(0, value.length());
    return parser->parseProtocolVersion(buffer, &cursor);
}
ProtocolVersion* parseProtocolVersion(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException) {
    if (buffer.capacity() == 0) throw IllegalArgumentException("Char array buffer may not be null");
    if (cursor == NULL) throw IllegalArgumentException("Parser cursor may not be null");
    std::string protoname  = protocol->getProtocol();
    int protolength = protoname.length();
    int indexFrom = cursor->getPos();
    int indexTo = cursor->getUpperBound();
    skipWhitespace(buffer, cursor);
    int i = cursor->getPos();
    if (i + protolength + 4 > indexTo) throw ParseException("Not a valid protocol version: %s", buffer.substring(indexFrom, indexTo).c_str());
    bool ok = true;
    for (int j=0; ok && (j<protolength); j++) {
        ok == (buffer.charAt(i+j) == protoname[j]);
    }
    if (ok) {
        ok = (buffer.charAt(i+protolength) == '/');
    }
    if (!ok) {
        throw ParseException("Not a valid protocol version: %s", buffer.substring(indexFrom, indexTo).c_str());
    }
    i += protolength+1;
    int period = buffer.indexOf('.', i, indexTo);
    if (period == -1) throw ParseException("Invalid protocol version number: %s", buffer.substring(indexFrom, indexTo).c_str());
    int major = Integer::parseInt(buffer.substringTrimmed(i, period).c_str());
    i = period + 1;
    int blank = buffer.indexOf(' ', i, indexTo);
    if (blank == -1)  blank = indexTo;
    int minor = Integer::parseInt(buffer.substringTrimmed(i, blank).c_str()); 
    cursor->updatePos(blank);
    return createProtocolVersion(major, minor);
}
bool hasProtocolVersion(CharArrayBuffer &buffer, ParserCursor *cursor) {
    if (cursor == NULL) throw  IllegalArgumentException("Parser cursor may not be null");
    int index = cursor->getPos();
    std::string protoname = protocol->getProtocol();
    int  protolength = protoname.length();
    if (buffer.length() < protolength+4) return false;
    if (index < 0) index = buffer.length() -4 -protolength;
    else if (index == 0) {
        while ((index < buffer.length()) && HTTP::isWhitespace(buffer.charAt(index))) index++;
    }
    if (index + protolength + 4 > buffer.length()) return false;
    bool
}
RequestLine* parseRequestLine(std::string value, LineParser *parser) throw (ParseException) {
}
RequestLine*parseRequestLine(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException) {
}
StatusLine* parseStatusLine(std::string value, LineParser *parser) throw (ParseException) {
}
StatusLine*parseStatusLine(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException) {
}
Header* parseHeader(std::string value, LineParser *parser) throw (ParseException) {
}
Header* parseHeader(CharArrayBuffer &buffer) throw (ParseException) {
}
