#include "HttpException.h"
#ifndef COOKIESPEC_H
#define COOKIESPEC_H
class Header;
class Cookie;
class CookieOrigin;
class CookieSpec {
    public:
    CookieSpec();
    virtual ~CookieSpec();
    virtual int getVersion() = 0;
    virtual void parse(Header *header, CookieOrigin *origin, vector<Cookie*> &list) throw(MalformedCookieException) = 0;
    virtual void validate(Cookie *cookie, CookieOrigin *) throw(MalformedCookieException) = 0;
    virtual bool match(Cookie *cookie, CookieOrigin *) throw (MalformedCookieException) = 0;
    virtual bool formatCookies(vector<Cookie*> &cookies, vector<Header *> headers) = 0;
    virtual Header* getVersionHeader() = 0;
};
#endif
