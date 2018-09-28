#include "HttpException.h"
#include "RefCount.h"
#ifndef COOKIESPECFACTORY_H
#define COOKIESPECFACTORY_H
class CookieSpecFactory : public RefCount {
    public:
    CookieSpecFactory();
    virtual ~CookieSpecFactory();
    virtual CookieSpec* newInstance(HttpParams *) = 0;
};
#endif
