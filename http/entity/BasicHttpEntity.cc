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
#include "AbstractHttpEntity.h"
#ifndef BASICHTTPENTITY_H
#include "BasicHttpEntity.h"
#endif
BasicHttpEntity::BasicHttpEntity() : content(NULL), contentObtained(false), length(0) { }
BasicHttpEntity::~BasicHttpEntity() {
    if (content) content->unref();
}
long BasicHttpEntity::getContentLength() {
    return length;
}
InputStream *BasicHttpEntity::getContent() throw(IOException, IllegalStateException) {
    if (content == NULL) throw IllegalStateException("Content has not been provided");
    if (contentObtained == true) throw IllegalStateException("Content has been consumed");
    contentObtained = true;
    content->ref();
    return content;
}
bool BasicHttpEntity::isRepeatable() {
    return false;
}
void BasicHttpEntity::setContentLength(long len) {
    length = len;
}
void BasicHttpEntity::setContent(InputStream *instream) {
    content = instream;
    if (content) content->ref();
    contentObtained = false;
}
void BasicHttpEntity::writeTo(OutputStream *outstream) throw (IOException) {
    if (outstream == NULL) throw IllegalArgumentException("Output stream may not be null");
    InputStream *instream = getContent();
    int l ;
    unsigned char tmp[2048];
    try {
        while ((l = instream->read((char *)tmp, 2048, 2048)) != -1) {
            outstream->write((char *)tmp, 2048, 0, l);
        }
    } catch (...) {
        instream->unref();
        throw;
    }
}
bool BasicHttpEntity::isStreaming() {
    return ((contentObtained == false) && (content != NULL));
}
void BasicHttpEntity::consumeContent() throw (IOException) {
    if (content!= NULL) content->close();
}
