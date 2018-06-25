#include "HttpException.h"
#ifndef NAMEVALUEPAIR_H
#define NAMEVALUEPAIR_H
class NameValuePair {
    public:
    virtual ~NameValuePair() { }
    virtual std::string getName() const = 0;
    virtual std::string getValue() const = 0;
};
#endif
