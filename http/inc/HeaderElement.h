#include "HttpException.h"
#include "NameValuePair.h"
#include "RefCount.h"
#ifndef HEADERELEMENT_H
#define HEADERELEMENT_H
class HeaderElement : public RefCount {
    public:
    virtual ~HeaderElement()  { }
    virtual std::string getName() const = 0;
    virtual std::string getValue() const = 0;
    virtual void getParameters(vector<NameValuePair *> &)= 0;
    virtual NameValuePair* getParameterByName(std::string name) = 0;
    virtual int getParameterCount() const = 0;
    virtual NameValuePair* getParameter(int index) = 0;
};
#endif
