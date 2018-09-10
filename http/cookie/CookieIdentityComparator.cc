#include "HttpException.h"
#include "StringUtils.h"
#include "Comparator.h"
#include "Cookie.h"
#ifndef COOKIEIDENTITYCOMPARATOR_H
#include "CookieIdentityComparator.h"
#endif
int CookieIdentityComparator::compare(Cookie &c1, Cookie &c2) {
    int res = (c1.getName() == c2.getName());
    if (res == 0) {
        std::string d1 = c1.getDomain();
        std::string d2 = c2.getDomain();
        res = compareIgnoreCase(d1, d2);
    }
    return res;
}
