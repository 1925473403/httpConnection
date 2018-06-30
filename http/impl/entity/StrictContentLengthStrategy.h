#include "HttpException.h"
#ifndef STRICTCONTENTLENGTHSTRATEGY_H
#define STRICTCONTENTLENGTHSTRATEGY_H
class StrictContentLengthStrategy : public ContentLengthStrategy {
    public:
        StrictContentLengthStrategy() { }
        ~StrictContentLengthStrategy() { }
        long determineLength(HttpMessage *message) throw (HttpException);
};
#endif
