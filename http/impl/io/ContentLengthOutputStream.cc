#include "HttpException.h"
#ifndef CONTENTLENGTHOUTPUTSTREAM_H
#include "ContentLengthOutputStream.h"
#endif
ContentLengthOutputStream(SessionOutputBuffer *outbuf, long contentlen) : out (NULL), contentLength (0), total(0), closed(false) {
    if (outbuf == NULL) throw IllegalArgumentException("Session output buffer may not be null");
    if (contentlen < 0) throw IllegalArgumentException("Content length may not be negative");
    out = outbuf;
    contentLength = contentlen;
}
ContentLengthOutputStream::ContentLengthOutputStream(const ContentLengthOutputStream &rhs) {
    out = rhs.out;
    contentLength = rhs.contentLength;
    total = rhs.total;
    closed = rhs.closed;
}
ContentLengthOutputStream& ContentLengthOutputStream::operator=(const ContentLengthOutputStream &rhs) {
    if (this != &rhs) {
        out = rhs.out;
        contentLength = rhs.contentLength;
        total = rhs.total;
        closed =rhs.closed;
    }
}
void ContentLengthOutputStream::close() throw (IOException) {
    if (!closed) {
        closed = true;
        out->flush();
    }
}
void ContentLengthOutputStream::flush() throw (IOException) {
    out->flush();
}
void ContentLengthOutputStream::write(byte *b, int blen, int off, int len) throw (IOException) {
    if (closed) throw IOException("Attempted write to closed stream.");
    if (total < contentLength) {
        long max = contentLength - total;
        if (len > max) {
            len = (int) max;
        }
        out->write(b, blen, off, len);
        total += len;
    }
}
void ContentLengthOutputStream::write(byte *b, int blen) throw (IOException) {
    write(b, blen, 0, blen);
}
void ContentLengthOutputStream::write(int b) throw (IOException) {
    if (closed) throw IOException("Attempted write to closed stream.");
    if (total < contentLength) {
        out->write(b);
        total++;
    }
}
