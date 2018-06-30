#include "HttpException.h"
#ifndef LAXCONTENTLENGTHSTRATEGY_H
#include "LaxContentLengthStrategy.h"
#endif
long LaxContentLengthStrategy::determineLength(HttpMessage *message) throw (HttpException) {
    if (message == NULL) throw IllegalArgumentException("HTTP message may not be null");
    HttpParams *params = message->getParams();
    bool strict = params->isParameterTrue(CoreProtocolsPNames::STRICT_TRANSFER_ENCODING);
    Header *transferEncodingHeader = message->getFirstHeader(HTTP::TRANSFER_ENCODING);
    Header *contentLengthHeader = message->getFirstHeader(HTTP::CONTENT_LEN);
    if (transferEncodingHeader != NULL) {
        vector<HeaderElement *> encodings;
        try {
            transferEncodingHeader->getElements(encodings);
        } catch (const ParseException &px) {
            throw ProtocolException("Invalid Transfer-Encoding header value: %s", px.what());
        }
        if (strict) {
            for (int i = 0; i < encodings.size(); i++) {
                std::string encoding = encodings[i]->getName();
                if (encoding.length() > 0 && !equalsIgnoreCase(HTTP::CHUNK_CODING, encoding) && !equalsIgnoreCase(HTTP::IDENTITY_CODING, encoding)) throw ProtocolException("Unsupported transfer encoding: %s", encoding.c_str());
            }
        }
        int len = encodings.size();
        if (equalsIgnoreCase(HTTP::IDENTITY_CODING, transferEncodingHeader->getValue())) return IDENTITY;
        else if ((len > 0) && (equalsIgnoreCase(HTTP::CHUNK_CODING, encodings[len -1]->getName()))) return CHUNKED;
        else {
            if (strict) throw ProtocolException("Chunk-encoding must be the last one applied");
            return IDENTITY;
        }
    } else if (contentLengthHeader != NULL) {
        long contentlen = -1;
        vector<Headers *> headers;
        message->getHeaders(HTTP::CONTENT_LEN, headers);
        if(strict && headers.size() > 1) throw ProtocolException("Multiple content length headers");
        for (int i = headers.size() -1; i >= 0; i--) {
            Headers *header = headers[i];
            contentlen = Integer::parseInt(header->getValue());
            if (contentlen > 0) break;
        }
        if (contentlen >= 0) return contentlen;
        else return IDENTITY;
    } else {
        return IDENTITY;
    }
}
