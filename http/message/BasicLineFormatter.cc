#include "HttpException.h"
#include "CharArrayBuffer.h"
#include "ProtocolVersion.h"
#include "RequestLine.h"
#include "StatusLine.h"
#include "Header.h"
#include "FormattedHeader.h"
#include "LineFormatter.h"
#include "Integer.h"
#ifndef BASICLINEFORMATTER_H
#include "BasicLineFormatter.h"
#endif
BasicLineFormatter BasicLineFormatter::DEFAULT;
CharArrayBuffer& BasicLineFormatter::initBuffer(CharArrayBuffer& buffer){
    buffer.clear();
    return buffer;
}

int BasicLineFormatter::estimateProtocolVersionLen(ProtocolVersion* version){
    return version->getProtocol().length() + 4; // room for "HTTP/1.1"
}

void BasicLineFormatter::doFormatRequestLine(CharArrayBuffer& buffer, RequestLine* reqline){
    std::string method = reqline->getMethod();
    std::string uri = reqline->getUri();
    int len = method.length() + 1 + uri.length() + 1 + estimateProtocolVersionLen(reqline->getProtocolVersion());
    buffer.ensureCapacity(len);

    buffer.append(method);
    buffer.append(' ');
    buffer.append(uri);
    buffer.append(' ');
    buffer = appendProtocolVersion(buffer, reqline->getProtocolVersion());
}

void BasicLineFormatter::doFormatStatusLine(CharArrayBuffer& buffer, StatusLine* statline){
    int len = estimateProtocolVersionLen(statline->getProtocolVersion()) + 1 + 3 + 1; // room for "HTTP/1.1 200 "
    std::string reason = statline->getReasonPhrase();
    if (reason.length() > 0) len += reason.length();
    buffer.ensureCapacity(len);
    appendProtocolVersion(buffer, statline->getProtocolVersion());
    buffer.append(' ');
    buffer.append(Integer::toString(statline->getStatusCode()).c_str());
    buffer.append(' '); // keep whitespace even if reason phrase is empty
    if (reason.length() > 0) buffer.append(reason);
}

void BasicLineFormatter::doFormatHeader(CharArrayBuffer& buffer, Header* header){
    std::string name = header->getName();
    std::string value = header->getValue();
    int len = name.length() + 2;
    if (value.length() > 0) len += value.length();
    buffer.ensureCapacity(len);
    buffer.append(name);
    buffer.append(": ");
    if (value.length() > 0) buffer.append(value);
}

std::string BasicLineFormatter::formatProtocolVersion(ProtocolVersion *version, LineFormatter* formatter){
    if (formatter == NULL) formatter = &(BasicLineFormatter::DEFAULT);
    CharArrayBuffer buffer(64);
    return formatter->appendProtocolVersion(buffer, version).toString();
}

CharArrayBuffer BasicLineFormatter::appendProtocolVersion(CharArrayBuffer& buffer, ProtocolVersion* version){
    if (version == NULL) throw IllegalArgumentException("Protocol version may not be null");
    CharArrayBuffer result = buffer;
    int len = estimateProtocolVersionLen(version);
    result.ensureCapacity(len);
    result.append(version->getProtocol().c_str());
    result.append('/'); 
    result.append(Integer::toString(version->getMajor()).c_str());
    result.append('.');
    result.append(Integer::toString(version->getMinor()).c_str());
    return result;
}

std::string BasicLineFormatter::formatRequestLine(RequestLine *reqline,LineFormatter* formatter){
    if (formatter == NULL) formatter = &(BasicLineFormatter::DEFAULT);
    CharArrayBuffer buffer(64);
    return formatter->formatRequestLine(buffer, reqline).toString();
}

CharArrayBuffer BasicLineFormatter::formatRequestLine(CharArrayBuffer& buffer, RequestLine * reqline){
    if (reqline == NULL) throw IllegalArgumentException("Request line may not be null");
    CharArrayBuffer result = initBuffer(buffer);
    doFormatRequestLine(result, reqline);
    return result;
}

std::string BasicLineFormatter::formatStatusLine(StatusLine* statline, LineFormatter* formatter){
    if (formatter == NULL) formatter = &(BasicLineFormatter::DEFAULT);
    CharArrayBuffer buffer(64);
    return formatter->formatStatusLine(buffer, statline).toString();
}

CharArrayBuffer BasicLineFormatter::formatStatusLine(CharArrayBuffer& buffer, StatusLine* statline){
    if (statline == NULL) throw IllegalArgumentException("Status line may not be null");
    CharArrayBuffer result = initBuffer(buffer);
    doFormatStatusLine(result, statline);
    return result;
}

std::string BasicLineFormatter::formatHeader(Header* header, LineFormatter* formatter){
    if (formatter == NULL) formatter = &(BasicLineFormatter::DEFAULT);
    CharArrayBuffer buffer(64);
    buffer = formatter->formatHeader(buffer, header);
    return buffer.toString();
}

CharArrayBuffer BasicLineFormatter::formatHeader(CharArrayBuffer& buffer, Header* header){
    if (header == NULL) throw IllegalArgumentException("Header may not be null");
    CharArrayBuffer result(64);
    if (dynamic_cast<FormattedHeader*>(header)) {
        result = (dynamic_cast<FormattedHeader*>(header))->getBuffer();
    } else {
        result = initBuffer(buffer);
        doFormatHeader(result, header);
    }
    return result;
}
