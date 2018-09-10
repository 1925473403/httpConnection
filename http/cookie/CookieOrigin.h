#include "HttpException.h"
#ifndef COOKIEORIGIN_H
#define COOKIEORIGIN_H
class CookieOrigin {
    std::string host;
    int port;
    std::string path;
    bool secure;
    public:
    CookieOrigin(std::string &h, int, std::string &p, bool secured) ;
    CookieOrigin(const CookieOrigin &);
    CookieOrigin& operator=(const CookieOrigin &);
    std::string getHost() const;
    int getPort() const;
    std::string getPath() const;
    bool isSecured() const;
    std::string toString() const;
};
#endif
