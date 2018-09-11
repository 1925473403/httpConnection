#include "HttpException.h"
#ifndef LAXCONTENTLENGTHSTRATEGY_H
#include "LaxContentLengthStrategy.h"
#endif
long LaxContentLengthStrategy::determineLength(HttpMessage *message) throw (HttpException) {
    if (message == NULL) throw IllegalArgumentException("HTTP message may not be null");
    HttpParams *params = message->getParams();
    bool strict = params->isParameterTrue(CoreProtocolsPNames::STRICT_TRANSFER_ENCODING);
    params->unref();
    Header *transferEncodingHeader = message->getFirstHeader(HTTP::TRANSFER_ENCODING);
    Header *contentLengthHeader = message->getFirstHeader(HTTP::CONTENT_LEN);
    if (transferEncodingHeader != NULL) {
        vector<HeaderElement *> encodings;
        try {
            transferEncodingHeader->getElements(encodings);
        } catch (const ParseException &px) {
            transferEncodingHeader->unref();
            throw ProtocolException("Invalid Transfer-Encoding header value: %s", px.what());
        }
        if (strict) {
            for (int i = 0; i < encodings.size(); i++) {
                std::string encoding = encodings[i]->getName();
                if (encoding.length() > 0 && !equalsIgnoreCase(HTTP::CHUNK_CODING, encoding) && !equalsIgnoreCase(HTTP::IDENTITY_CODING, encoding)) {
                    for (HeaderElement* he: encodings) {
                        if (he != NULL) he->unref();
                    }
                    transferEncodingHeader->unref();
                    throw ProtocolException("Unsupported transfer encoding: %s", encoding.c_str());
                }
            }
        }
        int len = encodings.size();
        if (equalsIgnoreCase(HTTP::IDENTITY_CODING, transferEncodingHeader->getValue())) {
            for (HeaderElement* he: encodings) {
                if (he != NULL) he->unref();
            }
            transferEncodingHeader->unref();
            return ContentLengthStrategy::IDENTITY;
        } else if ((len > 0) && (equalsIgnoreCase(HTTP::CHUNK_CODING, encodings[len -1]->getName()))) {
            for (HeaderElement* he: encodings) {
                if (he != NULL) he->unref();
            }
            transferEncodingHeader->unref();
            return ContentLengthStrategy::CHUNKED;
        } else {
            if (strict) throw ProtocolException("Chunk-encoding must be the last one applied");
            for (HeaderElement* he: encodings) {
                if (he != NULL) he->unref();
            }
            transferEncodingHeader->unref();
            return ContentLengthStrategy::IDENTITY;
        }
        transferEncodingHeader->unref();
    } else if (contentLengthHeader != NULL) {
        long contentlen = -1;
        vector<Headers *> headers;
        message->getHeaders(HTTP::CONTENT_LEN, headers);
        if(strict && headers.size() > 1) {
            for (Headers *h : headers) {
                if (h != NULL) h->unref();
            }
            contentLengthHeader->unref();
            throw ProtocolException("Multiple content length headers");
        }
        for (int i = headers.size() -1; i >= 0; i--) {
            Headers *header = headers[i];
            contentlen = Integer::parseInt(header->getValue());
            if (contentlen > 0) break;
        }
        if (contentlen >= 0) {
            for (Headers *h : headers) {
                if (h != NULL) h->unref();
            }
            contentLengthHeader->unref();
            return contentlen;
        } else {
            for (Headers *h : headers) {
                if (h != NULL) h->unref();
            }
            contentLengthHeader->unref();
            return ContentLengthStrategy::IDENTITY;
        }
        contentLengthHeader->unref();
    } else {
        return ContentLengthStrategy::IDENTITY;
    }
}
