#include "HttpException.h"
#include "Value.h"
#include "NameValuePair.h"
#include "HeaderElement.h"
#include "Header.h"
#include "HTTP.h"
#include "InputStream.h"
#include "ByteArrayInputStream.h"
#include "OutputStream.h"
#include "HttpEntity.h"
#include "BasicHeader.h"
#include "AbstractHttpEntity.h"
#include "ByteArrayInputStream.h"
#ifndef BYTEARRAYENTITY_H
#include "ByteArrayEntity.h"
#endif
ByteArrayEntity::ByteArrayEntity(byte *b, int blen) {
    if (b == NULL) throw IllegalArgumentException("Source byte array may not be null");
    content = b;
    contentlen = blen;
}
InputStream* ByteArrayEntity::getContent() throw (IOException, IllegalStateException) {
    return new ByteArrayInputStream(content, contentlen);
}
void ByteArrayEntity::writeTo(OutputStream *outstream) throw (IOException) {
    if (outstream == NULL) throw IllegalArgumentException("Output stream may not be null");
    outstream->write((char *)content, contentlen, contentlen);
}
