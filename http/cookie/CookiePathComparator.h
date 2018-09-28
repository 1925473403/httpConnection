#include "HttpException.h"
#include "StringUtils.h"
#include "Comparator.h"
#include "Cookie.h"
#ifndef COOKIEPATHCOMPARATOR_H
#define COOKIEPATHCOMPARATOR_H
class CookiePathComparator : public Comparator<Cookie> {
    std::string normalizePath(Cookie &c1);
    public:
    int compare(Cookie &c1, Cookie &c2);
};
#endif
