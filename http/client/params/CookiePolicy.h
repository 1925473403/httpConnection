#include "HttpException.h"
#ifndef COOKIEPOLICY_H
#define COOKIEPOLICY_H
class CookiePolicy {
    CookiePolicy() { }
    public:
        std::string BROWSER_COMPATIBILITY;
        std::string NETSCAPE;
        std::string RFC_2109;
        std::string RFC_2965;
        std::string BEST_MATCH;
};
#endif
