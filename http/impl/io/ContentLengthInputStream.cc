#include "HttpException.h"
#ifndef CONTENTLENGTHINPUTSTREAM_H
#include "ContentLengthInputStream.h"
#endif
int ContentLengthInputStream::BUFFER_SIZE = 2048;
ContentLengthInputStream::ContentLengthInputStream(SessionInputBuffer *inbuf, long contentLength) {
    if (inbuf == NULL) throw IllegalArgumentException("Input stream may not be null");
    if (contentLength < 0) throw IllegalArgumentException("Content length may not be negative");
    in = inbuf;
    contentLength = contentLength;
}
void ContentLengthInputStream::close() throw (IOException) {
    if (!closed) {
        try {
            byte buffer[BUFFER_SIZE];
            while (read(buffer, BUFFER_SIZE) >= 0) ;
        } catch (...) { }
        closed = true;
    }
}
int ContentLengthInputStream::read() throw (IOException) {
    if (closed) throw IOException("Attempted read from closed stream.");
    if (pos >= contentLength) return -1;
    pos++;
    return in->read();
}
int ContentLengthInputStream::read (byte *b, int blen, int off, int len) throw (IOException) {
    if (closed) throw IOException("Attempted read from closed stream.");
    if (pos >= contentLength) return -1;
    if (pos + len > contentLength) len = (int) (contentLength - pos);
    int count = in->read(b, blen, off, len);
    pos += count;
    return count;
}
int ContentLengthInputStream::read(byte *b, int blen) throw (IOException) {
    return read(b, blen, 0, blen);
}
long ContentLengthInputStream::skip(long n) throw (IOException) {
    if (n <= 0) return 0;
    byte buffer[BUFFER_SIZE];
    long remaining = std::min<int>(n, contentLength - pos);
    long count = 0;
    while (remaining > 0) {
        int l =  read(buffer, BUFFER_SIZE, 0, std::min<int>(BUFFER_SIZE, remaining));
        if (l == -1) break;
        count += l;
        remaining -= l;
    }
    pos += count;
    return count;
}
