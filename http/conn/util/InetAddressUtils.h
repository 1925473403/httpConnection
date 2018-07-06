#include "HttpException.h"
#ifndef INETADDRESSUTILS_H
#define INETADDRESSUTILS_H
class InetAddressUtils {
    private:
        InetAddressUtils() { }
    public:
        static regex IPV4_PATTERN;
        static regex IPV6_STD_PATTERN;
        static regex IPV6_HEX_COMPRESSED_PATTERN;
        static bool isIPv4Address(std::string &input);
        static bool isIPv6StdAddress(std::string &input);
        static bool isIPv6HexCompressedAddress(std::string &input);
};
#endif
