#include "HttpException.h"
#include "HeaderElement.h"
#include "FormattedHeader.h"
#include "ParserCursor.h"
#ifndef BUFFEREDHEADER_H
#include "BufferedHeader.h"
#endif
BufferedHeader::BufferedHeader(CharArrayBuffer &b) throw (ParseException) : buffer(b) {
    int colon = buffer.indexOf(':');
    if (colon == -1) throw ParseException("Invalid header: " + buffer.toString());
    std::string s = buffer.substringTrimmed(0, colon);
    if (s.length() == 0) throw ParseException("Invalid header: " + buffer.toString());
    name = s;
    valuePos = colon +1;
}
void BufferedHeader::getElements(vector<HeaderElement *> &res) throw (ParseException) {
    ParserCursor cursor = new ParserCursor(0, buffer.length());
    cursor.updatePos(valuePos);
    BasicHeaderValueParser::DEFAULT.parseElements(buffer, &cursor, res);
    return;
}
