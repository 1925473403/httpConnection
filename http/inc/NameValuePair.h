#include "HttpException.h"
#include "RefCount.h"
#ifndef NAMEVALUEPAIR_H
#define NAMEVALUEPAIR_H
class NameValuePair : public RefCount {
    public:
    virtual ~NameValuePair() { }
    virtual std::string getName() const = 0;
    virtual std::string getValue() const = 0;
};
#endif
