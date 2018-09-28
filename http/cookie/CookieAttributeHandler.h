#include "HttpException.h"
#ifndef COOKIEATTRIBUTEHANDLER_H
#define COOKIEATTRIBUTEHANDLER_H
class CookieAttributeHandler {
    public:
    virtual ~CookieAttributeHandler();
    virtual void parse(SetCookie *cookie, std::string &value) throw (MalformedCookieException) = 0;
    virtual void validate(Cookie *cookie, CookieOrigin *origin) throw( MalformedCookieException) = 0;
    virtual bool match(Cookie *cookie, CookieOrigin *origin) throw (MalformedCookieException) = 0;
};
#endif
