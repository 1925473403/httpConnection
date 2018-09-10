#include "HttpException.h"
#ifndef COOKIESPECFACTORY_H
#define COOKIESPECFACTORY_H
class CookieSpecFactory {
    public:
    CookieSpecFactory();
    virtual ~CookieSpecFactory();
    virtual CookieSpec* newInstance(HttpParams *) = 0;
};
#endif
