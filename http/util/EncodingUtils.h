#include "HttpException.h"
#ifndef ENCODINGUTILS_H
#define ENCODINGUTILS_H
class  EncodingUtils {
    typedef unsigned char byte;
    public:
    static std::string getString(byte *data, size_t, int, int, std::string &);
    static std::string getString(byte *date, size_t, std::string &);
    static void getBytes(std::string &data, byte* data, size_t, std::string &);
    static void getAsciiBytes(std::string &data, byte *data, size_t);
    static std::string getAsciiString(byte *data, size_t, int, int);
    static std::string getAsciiString(byte *data, size_t);
};
#endif
