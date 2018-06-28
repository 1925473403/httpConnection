#include "HttpException.h"
#ifndef COOKIEPOLICY_H
#define COOKIEPOLICY_H
class CookiePolicy {
    CookiePolicy() { }
    public:
        static std::string BROWSER_COMPATIBILITY;
        static std::string NETSCAPE;
        static std::string RFC_2109;
        static std::string RFC_2965;
        static std::string BEST_MATCH;
};
#endif
