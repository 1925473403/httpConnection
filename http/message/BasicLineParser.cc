#include "CharArrayBuffer.h"
#include "ParserCursor.h"
#include "ProtocolVersion.h"
#include "RequestLine.h"
#include "StatusLine.h"
#include "Header.h"
#include "LineParser.h"
#include "HeaderElement.h"
#include "FormattedHeader.h"
#include "Integer.h"
#include "HttpVersion.h"
#include "BasicRequestLine.h"
#include "BasicStatusLine.h"
#include "BufferedHeader.h"
#include "HTTP.h"
#include "BasicHeaderElement.h"
#include "BasicNameValuePair.h"
#ifndef BASICLINEPARSER_H
#include "BasicLineParser.h"
#endif
BasicLineParser BasicLineParser::DEFAULT;
ProtocolVersion* BasicLineParser::createProtocolVersion(int major, int minor) {
    return protocol->forVersion(major, minor);
}

void BasicLineParser::unref() {
    if (this == &(BasicLineParser::DEFAULT)) return;
    delete this;
}
RequestLine* BasicLineParser::createRequestLine(std::string method, std::string uri, ProtocolVersion *ver) {
    return new BasicRequestLine(method, uri, ver);
}
StatusLine* BasicLineParser::createStatusLine(ProtocolVersion *ver, int status, std::string reason) {
    return new BasicStatusLine(ver, status, reason);
}
void BasicLineParser::skipWhitespace(CharArrayBuffer &buffer, ParserCursor *cursor) {
    int pos = cursor->getPos();
    int indexTo = cursor->getUpperBound();
    while ((pos < indexTo) && HTTP::isWhitespace(buffer.charAt(pos))) pos++;
    cursor->updatePos(pos);
}
BasicLineParser::BasicLineParser(ProtocolVersion *proto) : LineParser(), protocol(proto) {
    if (proto == NULL) protocol = HttpVersion::HTTP_1_1;
}
BasicLineParser::BasicLineParser(): LineParser()  {
    protocol = HttpVersion::HTTP_1_1;
}
ProtocolVersion* BasicLineParser::parseProtocolVersion(std::string value, LineParser *parser) throw (ParseException) {
    if (value.length() == 0) throw IllegalArgumentException ("Value to parse may not be null.");
    if (parser == NULL) parser = &(BasicLineParser::DEFAULT);
    CharArrayBuffer buffer(value.length());
    buffer.append(value);
    ParserCursor cursor(0, value.length());
    return parser->parseProtocolVersion(buffer, &cursor);
}
ProtocolVersion* BasicLineParser::parseProtocolVersion(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException) {
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
bool BasicLineParser::hasProtocolVersion(CharArrayBuffer &buffer, ParserCursor *cursor) {
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
    bool ok = true;
    for (int j=0; ok && (j<protolength); j++) ok = (buffer.charAt(index+j) == protoname[j]);
    if (ok) ok = (buffer.charAt(index+protolength) == '/');
    return ok;
}
RequestLine* BasicLineParser::parseRequestLine(std::string value, LineParser *parser) throw (ParseException) {
    if (value.length() == 0) throw IllegalArgumentException("Value to parse may not be null.");
    if (parser == NULL) parser = &BasicLineParser::DEFAULT;
    CharArrayBuffer buffer(value.length());
    buffer.append(value);
    ParserCursor cursor(0, value.length());
    RequestLine *r = parser->parseRequestLine(buffer, &cursor);
    return r;
}
RequestLine* BasicLineParser::parseRequestLine(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException) {
    if (cursor == NULL) throw  IllegalArgumentException("Parser cursor may not be null");
    int indexFrom = cursor->getPos();
    int indexTo = cursor->getUpperBound();
    try {
        skipWhitespace(buffer, cursor);
        int i = cursor->getPos();
        int blank = buffer.indexOf(' ', i, indexTo);
        if (blank < 0) throw ParseException("Invalid request line: %s", buffer.substring(indexFrom, indexTo).c_str());
        std::string method = buffer.substringTrimmed(i, blank);
        cursor->updatePos(blank);
        skipWhitespace(buffer, cursor);
        i = cursor->getPos();
        blank = buffer.indexOf(' ', i, indexTo);
        if (blank < 0) throw ParseException("Invalid request line: %s", buffer.substring(indexFrom, indexTo).c_str());
        std::string uri = buffer.substringTrimmed(i, blank);
        cursor->updatePos(blank);
        ProtocolVersion *ver = parseProtocolVersion(buffer, cursor);
        skipWhitespace(buffer, cursor);
        if (!cursor->atEnd()) throw ParseException("Invalid request line: %s", buffer.substring(indexFrom, indexTo).c_str());
        return createRequestLine(method, uri, ver);
    } catch (const IndexOutOfBoundsException &e) {
        throw ParseException("Invalid request line: %s", buffer.substring(indexFrom, indexTo).c_str());
    }
    return 0;
}
StatusLine* BasicLineParser::parseStatusLine(std::string value, LineParser *parser) throw (ParseException) {
    if (value.length() == 0) throw IllegalArgumentException("Value to parse may not be null.");
    if (parser == NULL) parser = &BasicLineParser::DEFAULT;
    CharArrayBuffer buffer(value.length());
    buffer.append(value);
    ParserCursor cursor(0, value.length());
    StatusLine *s = parser->parseStatusLine(buffer, &cursor);
    return s;
}
StatusLine* BasicLineParser::parseStatusLine(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException) {
    if (cursor == NULL) throw  IllegalArgumentException("Parser cursor may not be null");
    int indexFrom = cursor->getPos();
    int indexTo = cursor->getUpperBound();
    try {
        ProtocolVersion *ver = parseProtocolVersion(buffer, cursor);
        skipWhitespace(buffer, cursor);
        int i = cursor->getPos();
        int blank = buffer.indexOf(' ', i, indexTo);
        if (blank < 0) blank = indexTo;
        int statusCode = 0;
        statusCode = Integer::parseInt(buffer.substringTrimmed(i, blank).c_str());
        i = blank;
        std::string reasonPhrase = "";
        if (i < indexTo) reasonPhrase = buffer.substringTrimmed(i, indexTo);
        return createStatusLine(ver, statusCode, reasonPhrase);
    } catch (const IndexOutOfBoundsException &e) {
        throw ParseException("Invalid request line: %s", buffer.substring(indexFrom, indexTo).c_str());
    }
    return NULL;
}
Header* BasicLineParser::parseHeader(std::string value, LineParser *parser) throw (ParseException) {
    if (value.length() == 0) throw IllegalArgumentException("Value to parse may not be null.");
    if (parser == NULL) parser = &BasicLineParser::DEFAULT;
    CharArrayBuffer buffer(value.length());
    buffer.append(value);
    Header *h = parser->parseHeader(buffer);
}
Header* BasicLineParser::parseHeader(CharArrayBuffer &buffer) throw (ParseException) {
    return new BufferedHeader(buffer);
}
