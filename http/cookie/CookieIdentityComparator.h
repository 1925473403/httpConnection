#include "HttpException.h"
#include "StringUtils.h"
#include "Comparator.h"
#include "Cookie.h"
#ifndef COOKIEIDENTITYCOMPARATOR_H
#define COOKIEIDENTITYCOMPARATOR_H
class CookieIdentityComparator : public Comparator<Cookie> {
    public:
    int compare(Cookie &c1, Cookie &c2) ;
};
#endif
