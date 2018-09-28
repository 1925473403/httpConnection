#include "HttpException.h"
#include "StringUtils.h"
#include "Comparator.h"
#include "Cookie.h"
#ifndef COOKIEPATHCOMPARATOR_H
#include "CookiePathComparator.h"
#endif
std::string CookiePathComparator::normalizePath(Cookie &cookie) {
    std::string path = cookie.getPath();
    if (path.length() == 0) {
        path = "/";
    }
    if (!ends_with(path, "/")) path += "/";
    return path;
}
int CookiePathComparator::compare(Cookie &c1, Cookie &c2) {
    std::string path1 = normalizePath(c1);
    std::string path2 = normalizePath(c2);
    if (path1 == path2) {
        return 0;
    } else if (starts_with(path1, path2)) return -1;
    else if (starts_with(path2, path1)) return 1;
    return 0;
}
