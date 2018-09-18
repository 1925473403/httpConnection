#include "HttpException.h"
#include <limits.h>
#include "ByteArrayBuffer.h"
#include "Value.h"
#include "NameValuePair.h"
#include "HeaderElement.h"
#include "Header.h"
#include "HTTP.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "HttpEntity.h"
#include "HttpEntityWrapper.h"
#include "BasicHeader.h"
#include "AbstractHttpEntity.h"
#include "ByteArrayInputStream.h"
#ifndef BUFFEREDHTTPENTITY_H
#include "BufferedHttpEntity.h"
#endif
BufferedHttpEntity::BufferedHttpEntity(HttpEntity *entity) :HttpEntityWrapper(entity) {
    if (entity->isRepeatable() == false || (entity->getContentLength() < 0)) {
        toByteArray(entity);
    } else {
        buffer = NULL;
        bufferlen = 0;
    }
}

BufferedHttpEntity::~BufferedHttpEntity() {
    if (buffer != NULL) delete[] buffer;
}

void BufferedHttpEntity::toByteArray(HttpEntity *entity) {
    if (entity == NULL) IllegalArgumentException("HTTP entity may not be null");
    InputStream *instream = entity->getContent();
    if (instream == NULL) {
        return;
    }
    if (entity->getContentLength() > INT_MAX) {
        throw IllegalArgumentException("HTTP entity too large to be buffered in memory");
    }
    int i = (int) entity->getContentLength();
    if (i < 0) i = 4096;
    ByteArrayBuffer buf(i);
    try {
        byte tmp[4096];
        int l;
        while ((l = instream->read((char *)tmp, 4096, 0, 4096)) != -1) {
            buf.append(tmp, 0, l);
        }
    } catch (...) { }
    instream->close();
    buffer = new byte[buf.length()];
    memcpy(buffer, buf.buffer(), buf.length());
    bufferlen = buf.length();
    return;
}

long BufferedHttpEntity::getContentLength() {
    if (buffer != NULL) return bufferlen;
    else wrappedEntity->getContentLength();
}
InputStream *BufferedHttpEntity::getContent() throw(IOException, IllegalStateException) {
    if (buffer != NULL) return new ByteArrayInputStream(buffer, bufferlen);
    else return wrappedEntity->getContent();
}
bool BufferedHttpEntity::isChunked() {
    return (buffer == NULL) && wrappedEntity->isChunked();
}
bool BufferedHttpEntity::isRepeatable() {
    return true;
}
void BufferedHttpEntity::writeTo(OutputStream* outstream) throw (IOException) {
    if (outstream == NULL) throw IllegalArgumentException("Output stream may not be null");
    if (buffer != NULL) {
        outstream->write((char *)buffer, bufferlen, bufferlen);
    } else {
        wrappedEntity->writeTo(outstream);
    }
}
bool BufferedHttpEntity::isStreaming() {
    return ((buffer == NULL) && (wrappedEntity->isStreaming()));
}
