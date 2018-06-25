#ifndef BYTEARRAYBUFFER_H
#include "ByteArrayBuffer.h"
#endif
#ifndef CHARARRAYBUFFER_H
#include "CharArrayBuffer.h"
#endif
typedef unsigned char byte;
void ByteArrayBuffer::expand(int newlen) {
    byte *newbuffer = new byte[std::max<int>((_capacity << 1), newlen)];
    memset(newbuffer, 0, std::max<int>((_capacity << 1), newlen));
    memcpy(newbuffer, _buffer, len);
    _capacity = std::max<int>((_capacity << 1), newlen);
    delete[] _buffer;
    _buffer = newbuffer;
}
ByteArrayBuffer::ByteArrayBuffer(int c) {
    if (c < 0) throw IllegalArgumentException("Buffer capacity may not be negative");
    _buffer = new byte[c];
    _capacity = c;
    memset(_buffer, 0, _capacity);
    len = 0;
}
ByteArrayBuffer::ByteArrayBuffer(const ByteArrayBuffer& rhs) {
    _buffer = new byte[rhs.capacity()];
    _capacity = rhs.capacity();
    memcpy(_buffer, rhs.buffer(), rhs.length());
    len = rhs.length();
}
ByteArrayBuffer& ByteArrayBuffer::operator=(const ByteArrayBuffer& rhs) {
    if (this != &rhs) {
    }
    return *this;
}
void ByteArrayBuffer::append(byte *b, int off, int l) {
    if (b == NULL) return;
    if ((off < 0) || (off > _capacity) || (l < 0) || ((off + l) < 0) || ((off + l) > _capacity)) {
        throw IndexOutOfBoundsException();
    }
    if (l == 0) return;
    int newlen =  len + l;
    if (newlen > _capacity) expand(newlen);
    memcpy(_buffer + len, b + off, l - off);
    len = newlen;
}
void ByteArrayBuffer::append(std::string &s) {
    if (s.length() == 0) return;
    int _strlen = s.length();
    int newlen = len + _strlen;
    if (newlen > _capacity) expand(newlen);
    memcpy(_buffer + len, s.c_str(), _strlen);
    len = newlen;
}
void ByteArrayBuffer::append(ByteArrayBuffer &b) {
    append(b._buffer, 0, b.len);
}
void ByteArrayBuffer::append(char ch) {
    int newlen = len + 1;
    if (newlen > _capacity) expand(newlen);
    _buffer[len] = ch;
    len ++;
}
void ByteArrayBuffer::append(int l) {
    char pStr[128] = { 0 };
    snprintf(pStr, 128, "%ld", l);
    int _strlen = strlen(pStr);
    int newlen = len + _strlen;
    if (newlen > _capacity) expand(newlen);
    sprintf((char *)_buffer + len, "%s", pStr);
    len += _strlen;
}
void ByteArrayBuffer::append(float f) {
    char pStr[128] = { 0 };
    snprintf(pStr, 128, "%f", f);
    int _strlen = strlen(pStr);
    int newlen = len + _strlen;
    if (newlen > _capacity) expand(newlen);
    sprintf((char *)_buffer + len, "%s", pStr);
    len += _strlen;
}
void ByteArrayBuffer::append(CharArrayBuffer &b, int off, int l) {
    append(reinterpret_cast<byte*>(b.buffer()), off, l);
}
void ByteArrayBuffer::clear() {
    len = 0;
}
std::string ByteArrayBuffer::toString() {
    std::string res((char *)_buffer, len);
    return res;
}
byte ByteArrayBuffer::byteAt(int i) {
    return _buffer[i];
}
void ByteArrayBuffer::ensureCapacity(int required) {
    int available = _capacity - len;
    if (required > available) expand(len + required);
}
byte* ByteArrayBuffer::toByteArray() { return _buffer; }
void ByteArrayBuffer::setLength(int l) {
    if (len < 0 || len > _capacity) throw IndexOutOfBoundsException();
    len = l;
}
