#include "HttpException.h"
#include "Value.h"
#include "NameValuePair.h"
#include "HeaderElement.h"
#include "Header.h"
#include "HTTP.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "HttpEntity.h"
#include "BasicHeader.h"
#ifndef ABSTRACTHTTPENTITY_H
#include "AbstractHttpEntity.h"
#endif
AbstractHttpEntity::AbstractHttpEntity() : contentType(NULL), contentEncoding(NULL), chunked(false) { }
AbstractHttpEntity::~AbstractHttpEntity() {
    if (contentType != NULL) contentType->unref();
    if (contentEncoding != NULL) contentEncoding->unref();
    chunked = false;
}
Header* AbstractHttpEntity::getContentType() {
    if (contentType != NULL) contentType->ref();
    return contentType;
}
Header* AbstractHttpEntity::getContentEncoding() {
    if (contentEncoding != NULL) contentEncoding->ref();
    return contentEncoding;
}
bool AbstractHttpEntity::isChunked() {
    return chunked;
}
void AbstractHttpEntity::setContentType(Header *h) {
    contentType = h;
    if (contentType) contentType->ref();
}
void AbstractHttpEntity::setContentType(std::string &s) {
    Header *h = NULL;
    if (s.empty() == false) h = new BasicHeader(HTTP::CONTENT_ENCODING, s);
    setContentType(h);
}

void AbstractHttpEntity::setContentEncoding(Header *h) {
    contentEncoding = h;
    if (contentEncoding) contentEncoding->ref();
}
void AbstractHttpEntity::setContentEncoding(std::string &s) {
    Header *h = NULL;
    if (s.empty() == false) h = new BasicHeader(HTTP::CONTENT_ENCODING, s);
    setContentEncoding(h);
}
void AbstractHttpEntity::setChunked(bool b) {
    chunked = b;
}
void AbstractHttpEntity::consumeContent() throw (IOException) {
    if (isStreaming()) throw IOException ("streaming entity does not implement consumeContent()");
}
