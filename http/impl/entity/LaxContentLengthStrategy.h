#include "HttpException.h"
#ifndef LAXCONTENTLENGTHSTRATEGY_H
#define LAXCONTENTLENGTHSTRATEGY_H
class LaxContentLengthStrategy : public ContentLengthStrategy {
    public:
        LaxContentLengthStrategy() { }
        ~LaxContentLengthStrategy() { }
        long determineLength(HttpMessage *message) throw (HttpException);
};
#endif
