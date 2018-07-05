#include "HttpException.h"
#ifndef IDENTITYINPUTSTREAM_H
#include "IdentityInputStream.h"
#endif
IdentityInputStream::IdentityInputStream(SessionInputBuffer *inbuf) : in(NULL), closed(false) {
    if (inbuf == NULL) throw IllegalArgumentException("Session input buffer may not be null");
    in = inbuf;
}
int IdentityInputStream::available() throw(IOException) {
    if (!closed && in->isDataAvailable(10)) return 1;
    return 0;
}
void IdentityInputStream::close() throw(IOException) {
    closed = true;
}
int IdentityInputStream::read() throw(IOException) {
    if (closed) return -1;
    return in->read();
}
int IdentityInputStream::read(byte *b, int blen, int off, int len) throw(IOException) {
    if (closed) return -1;
    return in->read(b, blen, off, len);
}
