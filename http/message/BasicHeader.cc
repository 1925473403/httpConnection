#include "HttpException.h"
#include "CharArrayBuffer.h"
#include "ProtocolVersion.h"
#include "RequestLine.h"
#include "StatusLine.h"
#include "Header.h"
#include "FormattedHeader.h"
#include "LineFormatter.h"
#include "BasicLineFormatter.h"
#include "HeaderValueParser.h"
#include "BasicHeaderValueParser.h"
#ifndef BASICHEADER_H
#include "BasicHeader.h"
#endif
std::string BasicHeader::toString() {
    CharArrayBuffer buffer(64);
    std::string res = BasicLineFormatter::DEFAULT.formatHeader(buffer, this).toString();
    return res;
}
void BasicHeader::getElements(vector<HeaderElement*> &res) throw (ParseException) {
    if (value.length() > 0) BasicHeaderValueParser::parseElements(value, NULL, res);
    return ;
}
BasicHeader::BasicHeader(std::string &n, std::string &v) : name(n), value(v) {
    if (name.length() == 0) throw IllegalArgumentException("Name may not be null");
}

BasicHeader::BasicHeader(std::string &n, std::string &&v) : name(n), value(std::move(v)) {
    if (name.length() == 0) throw IllegalArgumentException("Name may not be null");
}
