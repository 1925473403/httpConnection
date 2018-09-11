#include "HttpException.h"
#include "HeaderElement.h"
#include "RefCount.h"
#ifndef HEADERELEMENTITERARTOR_H
#define HEADERELEMENTITERARTOR_H
class HeaderElementIterator : public RefCount {
    public:
    virtual ~HeaderElementIterator() { }
    virtual bool hasNext() = 0;
    virtual HeaderElement* nextElement() = 0;
};
#endif
