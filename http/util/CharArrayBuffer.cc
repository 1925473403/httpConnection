#ifndef CHARARRAYBUFFER_H
#include "CharArrayBuffer.h"
#endif
#ifndef BYTEARRAYBUFFER_H
#include "ByteArrayBuffer.h"
#endif
#include "HTTP.h"
void CharArrayBuffer::expand(int newlen) {
    char *newbuffer = new char[std::max<int>((_capacity << 1), newlen)];
    memset(newbuffer, 0, std::max<int>((_capacity << 1), newlen));
    memcpy(newbuffer, _buffer, len);
    _capacity = std::max<int>((_capacity << 1), newlen);
    delete[] _buffer;
    _buffer = newbuffer;
}
CharArrayBuffer::CharArrayBuffer(int c) {
    if (c < 0) throw IllegalArgumentException("Buffer capacity may not be negative");
    _buffer = new char[c];
    _capacity = c;
    memset(_buffer, 0, c);
    len = 0;
}
CharArrayBuffer::CharArrayBuffer(const CharArrayBuffer& rhs) {
    _buffer = new char[rhs.capacity()];
    _capacity = rhs.capacity();
    memcpy(_buffer, rhs.buffer(), rhs.length());
    len = rhs.length();
}
CharArrayBuffer& CharArrayBuffer::operator=(const CharArrayBuffer& rhs) {
    if (this != &rhs) {
        delete[] _buffer;
        _capacity = rhs.capacity();
        len = rhs.length();
        _buffer = new char[_capacity];
        memcpy(_buffer, rhs.buffer(), len);
    }
    return *this;
}
void CharArrayBuffer::append(char *b, int off, int l) {
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
void CharArrayBuffer::append(std::string &s) {
    if (s.length() == 0) return;
    int _strlen = s.length();
    int newlen = len + _strlen;
    if (newlen > _capacity) expand(newlen);
    memcpy(_buffer + len, s.c_str(), _strlen);
    len = newlen;
}
void CharArrayBuffer::append(const char *s) {
    if (s == NULL) return;
    int _strlen = strlen(s);
    int newlen = len + _strlen;
    if (newlen > _capacity) expand(newlen);
    memcpy(_buffer + len, s, _strlen);
    len += _strlen;
}
void CharArrayBuffer::append(CharArrayBuffer &b) {
    append(b._buffer, 0, b.len);
}
void CharArrayBuffer::append(char ch) {
    int newlen = len + 1;
    if (newlen > _capacity) expand(newlen);
    _buffer[len] = ch;
    len ++;
}
void CharArrayBuffer::append(int l) {
    char pStr[128] = { 0 };
    snprintf(pStr, 128, "%d", l);
    int _strlen = strlen(pStr);
    int newlen = len + _strlen;
    if (newlen > _capacity) expand(newlen);
    sprintf(_buffer + len, "%s", pStr);
    len += _strlen;
}
void CharArrayBuffer::append(float f) {
    char pStr[128] = { 0 };
    snprintf(pStr, 128, "%f", f);
    int _strlen = strlen(pStr);
    int newlen = len + _strlen;
    if (newlen > _capacity) expand(newlen);
    sprintf(_buffer + len, "%s", pStr);
    len += _strlen;
}
void CharArrayBuffer::append(ByteArrayBuffer &b, int off, int l) {
    append(reinterpret_cast<char*>(b.buffer()), off, l);
}
void CharArrayBuffer::clear() {
    len = 0;
}
char *CharArrayBuffer::buffer() { return _buffer; }
std::string CharArrayBuffer::toString() { 
    std::string res(_buffer);
    return res;
}
char CharArrayBuffer::charAt(int i) {
    return _buffer[i];
}
void CharArrayBuffer::ensureCapacity(int required) {
    int available = _capacity - len;
    if (required > available) expand(len + required);
}
char *CharArrayBuffer::toCharArray() {
    return _buffer;
}
void CharArrayBuffer::setLength(int l) {
    if (len < 0 || len > _capacity) throw IndexOutOfBoundsException();
    len = l;
}

int CharArrayBuffer::indexOf(int ch, int beginIndex, int endIndex) {
    if (beginIndex < 0) beginIndex = 0;
    if (endIndex > len) endIndex = len;
    if (beginIndex > endIndex) return -1;
    for (int i = beginIndex; i < endIndex; i++) if (_buffer[i] == ch) return i;
    return -1;
}

int CharArrayBuffer::indexOf(int ch) {
    return indexOf(ch, 0, len);
}
std::string CharArrayBuffer::substring(int beginIndex, int endIndex) {
    if (beginIndex < 0) throw IndexOutOfBoundsException();
    if (endIndex > len)  throw IndexOutOfBoundsException();
    if (beginIndex > endIndex)  throw IndexOutOfBoundsException();
    return std::string(reinterpret_cast<const char *>(_buffer + beginIndex), endIndex - beginIndex);
}

std::string CharArrayBuffer::substringTrimmed(int beginIndex, int endIndex) {
    if (beginIndex < 0) throw IndexOutOfBoundsException();
    if (endIndex > len)  throw IndexOutOfBoundsException();
    if (beginIndex > endIndex)  throw IndexOutOfBoundsException();
    while (beginIndex < endIndex && HTTP::isWhitespace(_buffer[beginIndex])) beginIndex++;
    while (endIndex > beginIndex && HTTP::isWhitespace(_buffer[endIndex - 1])) endIndex--;
    return std::string(reinterpret_cast<const char *>(_buffer + beginIndex), endIndex - beginIndex);
}
