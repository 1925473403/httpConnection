#include "HttpException.h"
#ifndef COOKIESPECPNAMES_H
#define COOKIESPECPNAMES_H
class CookieSpecPNames {
    public:
    virtual ~CookieSpecPNames() { }
    static std::string DATE_PATTERNS;
    static std::string SINGLE_COOKIE_HEADER;
};
#endif
