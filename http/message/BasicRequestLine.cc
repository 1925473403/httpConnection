#include "CharArrayBuffer.h"
#include "ProtocolVersion.h"
#include "RequestLine.h"
#include "StatusLine.h"
#include "Header.h"
#include "FormattedHeader.h"
#include "LineFormatter.h"
#include "Integer.h"
#include "BasicLineFormatter.h"
#ifndef BASICREQUESTLINE_H
#include "BasicRequestLine.h"
#endif
BasicRequestLine::BasicRequestLine(std::string m, std::string u, ProtocolVersion *version):method(m), uri(u), protoversion(version) {
    if (method.length() == 0) throw IllegalArgumentException("Method must not be null.");
    if (u.length() == 0) throw IllegalArgumentException("URI must not be null.");
    if (version == NULL) throw IllegalArgumentException("Protocol version must not be null.");
}

std::string BasicRequestLine::toString() {
    CharArrayBuffer buffer(64);
    std::string s = BasicLineFormatter::DEFAULT.formatRequestLine(buffer, this).toString();
    return s;
}
