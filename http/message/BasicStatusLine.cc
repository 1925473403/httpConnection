#include "CharArrayBuffer.h"
#include "ProtocolVersion.h"
#include "RequestLine.h"
#include "StatusLine.h"
#include "Header.h"
#include "FormattedHeader.h"
#include "LineFormatter.h"
#include "BasicLineFormatter.h"
#ifndef BASICSTATUSLINE_H
#include "BasicStatusLine.h"
#endif
BasicStatusLine::BasicStatusLine(ProtocolVersion *version, int sc, std::string r) : protoVersion(version), statusCode(sc), reasonPhrase(r) {
    if (version == NULL) throw IllegalArgumentException("Protocol version may not be null.");
    if (statusCode < 0) throw IllegalArgumentException("Status code may not be negative.");
    protoVersion->ref();
}
BasicStatusLine::~BasicStatusLine() {
    if (protoVersion != NULL) protoVersion->unref();
}
int BasicStatusLine::getStatusCode() { return statusCode; }
ProtocolVersion *BasicStatusLine::getProtocolVersion() { return protoVersion; }
std::string BasicStatusLine::getReasonPhrase() { return reasonPhrase; }
std::string BasicStatusLine::toString() {
    CharArrayBuffer buffer(64);
    std::string str = BasicLineFormatter::DEFAULT.formatStatusLine(buffer, this).toString();
    return str;
}
