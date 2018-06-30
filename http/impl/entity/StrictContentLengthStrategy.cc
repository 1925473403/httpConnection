#include "HttpException.h"
#include "StringUtils.h"
#include "ContentLengthStrategy.h"
#include "HttMessage.h"
#include "Header.h"
#include "HttpVersion.h"
#ifndef STRICTCONTENTLENGTHSTRATEGY_H
#include "StrictContentLengthStrategy.h"
#endif
long StrictContentLengthStrategy::determineLength(HttpMessage *message) throw (HttpException) {
    if (message == NULL) throw IllegalArgumentException("HTTP message may not be null");
    Header *transferEncodingHeader = message->getFirstHeader(HTTP::TRANSFER_ENCODING);
    Header *contentLengthHeader = message->getFirstHeader(HTTP::CONTENT_LEN);
    if (transferEncodingHeader != NULL) {
        std::string s = transferEncodingHeader->getValue();
        if (equalsIgnoreCase(s, HTTP::CHUNK_CODING) {
            if (message->getProtocolVersion()->lessEquals(HttpVersion::HTTP_1_0)) throw ProtocolException("Chunked transfer encoding not allowed for %s", message->getProtocolVersion()->toString());
            return CHUNKED;
        } else if (equalsIgnoreCase(s, HTTP::IDENTITY_CODING)) {
            return IDENTITY;
        } else throw ProtocolException("Unsupported transfer encoding: %s", s.c_str());
    } else if (contentLengthHeader != NULL) {
        std::string s = contentLengthHeader->getValue();
        long len = Integer::parseInt(s);
        return len;
    } else return IDENTITY;
}
