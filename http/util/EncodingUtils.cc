#include "HttpException.h"
#ifndef ENCODINGUTILS_H
#include "EncodingUtils.h"
#endif
typedef unsigned char byte;
std::string EncodingUtils::getString(byte *data, size_t n, int offset, int length, std::string &charset) {
}
std::string EncodingUtils::getString(byte *date, size_t n, std::string &charset) {
}
void EncodingUtils::getBytes(std::string &data, byte* data, size_t n, std::string &charset) {
}
void EncodingUtils::getAsciiBytes(std::string &data, byte *data, size_t n) {
}
std::string EncodingUtils::getAsciiString(byte *data, size_t n, int offset, int length) {
    if (data == nullptr) throw IllegalArgumentException("Parameter may not be null");
    try {
    } 
}
std::string EncodingUtils::getAsciiString(byte *data, size_t n) {
    if (data == nullptr) throw IllegalArgumentException("Parameter may not be null");
    getAsciiString(data, n, 0, data.length);
    return;
}
