#include "HttpException.h"
#include "HeaderElement.h"
#ifndef HEADER_H
#define HEADER_H
class Header {
    public:
    virtual ~Header() { }
    virtual std::string getName() = 0;
    virtual std::string getValue() = 0;
    virtual void getElements(vector<HeaderElement *> &) throw (ParseException) = 0;
};
#endif
