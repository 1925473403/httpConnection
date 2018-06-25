#include "HttpException.h"
#ifndef TOKENITERATOR_H
#define TOKENITERATOR_H
class TokenIterator {
    public:
    virtual ~TokenIterator() = 0;
    virtual bool hasNext() = 0;
    virtual std::string nextToken() = 0;
};
#endif
