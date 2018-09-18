#include "HttpException.h"
#include "Value.h"
#include "NameValuePair.h"
#include "HeaderElement.h"
#include "Header.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "HttpEntity.h"
#ifndef HTTPENTITYWRAPPER_H
#include "HttpEntityWrapper.h"
#endif
HttpEntityWrapper::HttpEntityWrapper(HttpEntity *w):wrappedEntity(w) {
    if (w == NULL) throw IllegalArgumentException ("wrapped entity must not be null");
    w->ref();
}
HttpEntityWrapper::~HttpEntityWrapper() { wrappedEntity->unref(); }
bool HttpEntityWrapper::isRepeatable() {
    return wrappedEntity->isRepeatable();
}
bool HttpEntityWrapper::isChunked() {
    return wrappedEntity->isChunked();
}
long HttpEntityWrapper::getContentLength() {
    return wrappedEntity->getContentLength();
}
Header* HttpEntityWrapper::getContentType() {
    return wrappedEntity->getContentType();
}
Header* HttpEntityWrapper::getContentEncoding() {
    return wrappedEntity->getContentEncoding();
}
InputStream* HttpEntityWrapper::getContent() throw (IOException, IllegalStateException) {
    return wrappedEntity->getContent();
}
void HttpEntityWrapper::writeTo(OutputStream *outstream) throw (IOException) {
    wrappedEntity->writeTo(outstream);
}
bool HttpEntityWrapper::isStreaming() {
    return wrappedEntity->isStreaming();
}
void HttpEntityWrapper::consumeContent() throw(IOException) {
    wrappedEntity->consumeContent();
}
