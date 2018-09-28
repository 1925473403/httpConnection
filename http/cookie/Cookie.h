#include "HttpException.h"
#include "RefCount.h"
#ifndef COOKIE_H
#define COOKIE_H
class Cookie : public RefCount {
    public:
    virtual std::string getName() = 0;
    virtual std::string getValue() = 0;
    virtual std::string getComment() = 0;
    virtual std::string getCommentURL() = 0;
    virtual std::string getExpiryDate() = 0;
    virtual bool isPersistent() = 0;
    virtual std::string getDomain() = 0;
    virtual std::string getPath() = 0;
    virtual void getPorts(vector<int> &ports) = 0;
    virtual bool isSecure() = 0;
    virtual int getVersion() = 0;
    virtual bool isExpired() = 0;
    virtual ~Cookie() ;
};
#endif
