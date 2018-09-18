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
#ifndef INPUTSTREAMENTITY_H
#include "InputStreamEntity.h"
#endif
InputStreamEntity::InputStreamEntity(InputStream *instream, long len) {
    if (instream == NULL) throw IllegalArgumentException("Source input stream may not be null");
    content = instream;
    content->ref();
    length = len;
}
InputStreamEntity::~InputStreamEntity() {
    if (content) content->unref();
    length = -1;
}
InputStream* InputStreamEntity::getContent() throw(IOException, IllegalStateException) {
    content->ref();
    return content;
}
void InputStreamEntity::writeTo(OutputStream *outstream) throw(IOException) {
    if (outstream == NULL) throw IllegalArgumentException("Output stream may not be null");
    InputStream *instream = content;
    byte buf[4096] = { 0 };
    int l;
    if (length <0) {
        while ((l = instream->read((char *)buf, 4096, 4096)) != -1) {
            outstream->write((char *)buf, 4096, 0, l);
        }
    } else {
        long remaining = length;
        while (remaining > 0) {
            l = instream->read((char *)buf, 4096, 0, std::min<int>(4096, remaining));
            if (l == -1) break;
            outstream->write((char *)buf, 4096, 0, l);
            remaining -= l;
        }
    }
    consumed = true;
}
bool InputStreamEntity::isStreaming() {
    return (!consumed);
}
void InputStreamEntity::consumeContent() throw(IOException) {
    consumed = true;
    content->close();
}
