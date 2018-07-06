#include "HttpException.h"
#include <regex>
#ifndef INETADDRESSUTILS_H
#include "InetAddressUtils.h"
#endif
regex InetAddressUtils::IPV4_PATTERN("^(25[0-5]|2[0-4][[:d:]]|[0-1]?[[:d:]]?[[:d:]])(\.(25[0-5]|2[0-4][[:d:]]|[0-1]?[[:d:]]?[[:d:]])){3}$");
regex InetAddressUtils::IPV6_STD_PATTERN("^(?:[0-9a-fA-F]{1,4}:){7}[0-9a-fA-F]{1,4}$");
regex InetAddressUtils::IPV6_HEX_COMPRESSED_PATTERN("^((?:[0-9A-Fa-f]{1,4}(?::[0-9A-Fa-f]{1,4})*)?)::((?:[0-9A-Fa-f]{1,4}(?::[0-9A-Fa-f]{1,4})*)?)$");
bool InetAddressUtils::isIPv4Address(std::string &input) {
    return regex_match(input, InetAddressUtils::IPV4_PATTERN);
}
bool InetAddressUtils::isIPv6StdAddress(std::string &input) {
    return regex_match(input, InetAddressUtils::IPV6_STD_PATTERN);
}
bool InetAddressUtils::isIPv6HexCompressedAddress(std::string &input) {
    return regex_match(input, InetAddressUtils::IPV6_HEX_COMPRESSED_PATTERN);
}
