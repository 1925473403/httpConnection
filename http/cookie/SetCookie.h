#include "HttpException.h"
#ifndef SETCOOKIE_H
#define SETCOOKIE_H
class SetCookie : public Cookie {
    public:
    virtual void setValue(std::string &) = 0;
    virtual void setComment(std::string &) = 0;
    virtual void setExpiryDate(std::string &date) = 0;
    virtual void setDomain(std::string &) = 0;
    virtual void setPath(std::string &) = 0;
    virtual void setSecure(bool s) = 0;
    virtual void setVersion(int) = 0;
    virtual ~SetCookie();
};
#endif
