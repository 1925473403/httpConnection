#include "HttpException.h"
#ifndef IDENTITYOUTPUTSTREAM_H
#include "IdentityOutputStream.h"
#endif
IdentityOutputStream::IdentityOutputStream(SessionOutputBuffer *outbuf) : closed(false) {
    if (outbuf == NULL) throw IllegalArgumentException("Session output buffer may not be null");
    out = outbuf;
}
void IdentityOutputStream::close() throw (IOException) {
    if (!closed) {
        closed = true;
        out->flush();
    }
}
void IdentityOutputStream::flush() throw (IOException) {
    out->flush();
}
void IdentityOutputStream::write(byte *b, int blen, int off, int len) throw (IOException) {
    if (closed) throw IOException("Attempted write to closed stream.");
    out->write(b, blen, off, len);
}
void IdentityOutputStream::write(byte *b, int blen) throw (IOException) {
    write(b, blen, 0, blen);
}
void IdentityOutputStream::write(int b) throw (IOException) {
    if (closed) throw IOException("Attempted write to closed stream.");
    out->write(b);
}
