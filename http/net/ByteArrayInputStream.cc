#include "HttpException.h"
#include "InputStream.h"
#ifndef BUFFEREDINPUTSTREAM_H
#include "ByteArrayInputStream.h"
#endif
ByteArrayInputStream::ByteArrayInputStream(byte *b, int len):buf(0), buflen(0), pos(0), _mark(0), count(0) {
    buf = b;
    buflen = len;
    count = len;
}
ByteArrayInputStream::ByteArrayInputStream::ByteArrayInputStream(byte *b, int len, int off, int length) {
    buf = b;
    buflen = len;
    pos = off;
    count = std::min<int>(off + length, len);
    _mark = off;
}
int ByteArrayInputStream::read() throw (IOException){
    int ret = -1;
    if (pos < count) {
        ret = buf[pos++] & 0xff;
    }
    return ret;
}

int ByteArrayInputStream::read(char *b, int blen, int len) throw (IOException) {
    return read(b, blen, 0, len);
}

int ByteArrayInputStream::read(char *b, int blen, int off, int len) throw (IOException) {
    if (b == NULL) throw NullPointerException();
    else if (off < 0||len < 0|| len > buflen - off) throw IndexOutOfBoundsException();
    if (pos >= count) return -1;
    int avail = count - pos;
    if (len > avail) len = avail;
    if (len <= 0) return 0;
    memcpy(b+off, buf+pos, len);
    pos += len;
    return len;
}
long ByteArrayInputStream::skip(long n) throw (IOException) {
    long k = count - pos;
    if (n < k) {
        k = ((n < 0)?0:n);
    }
    pos += k;
    return k;
}
int ByteArrayInputStream::available() throw (IOException) {
    return count - pos;
}
bool ByteArrayInputStream::markSupported() {
    return true;
}
void ByteArrayInputStream::mark(int readAheadLimit) {
    _mark = pos;
}
void ByteArrayInputStream::reset() {
    pos = _mark;
}
void ByteArrayInputStream::close() throw (IOException) {
}
