#include "HttpException.h"
#include "Header.h"
#include "RefCount.h"
#ifndef HEADERITERARTOR_H
#define HEADERITERARTOR_H
class HeaderIterator : public RefCount {
    public:
    virtual ~HeaderIterator()  { }
    virtual bool hasNext() = 0;
    virtual Header* nextHeader() = 0;
};
#endif
