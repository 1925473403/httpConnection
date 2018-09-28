#include "HttpException.h"
#include "StringUtils.h"
#include "Cookie.h"
#ifndef COOKIEORIGIN_H
#include "CookieOrigin.h"
#endif
CookieOrigin::CookieOrigin(std::string &h, int pt, std::string &p, bool secured) {
    trim(h);
    if (h.length() == 0) throw IllegalArgumentException("Host cannot be null");
    if (pt< 0) throw IllegalArgumentException("Invalid port: %d", port);
    if (p.length()) throw IllegalArgumentException("Path of origin may not be null.");
    toLowerCase(h);
    host = h;
    port = pt;
    trim(p);
    if (p.length() != 0) path = p;
    else path = "/";
    secure = secured;
}
CookieOrigin::CookieOrigin(const CookieOrigin &rhs) {
    host = rhs.getHost();
    port = rhs.getPort();
    path = rhs.getPath();
    secure = rhs.isSecured();
}
CookieOrigin& CookieOrigin::operator=(const CookieOrigin &rhs) {
    if (this != &rhs) {
        host = rhs.getHost();
        port = rhs.getPort();
        path = rhs.getPath();
        secure = rhs.isSecured();
    }
    return *this;
}
std::string CookieOrigin::getHost() const {
    return host;
}
int CookieOrigin::getPort() const {
    return port;
}
std::string CookieOrigin::getPath() const {
    return path;
}
bool CookieOrigin::isSecured() const {
    return secure;
}
std::string CookieOrigin::toString() const {
    std::stringstream ss;
    ss << "[" ;
    if (secure) ss << "(secure)";
    ss << host << ":" << port << path<<"]";
    return ss.str();
}
