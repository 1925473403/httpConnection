#include "HttpException.h"
#ifndef CONTENTLENGTHSTRATEGY_H
#define CONTENTLENGTHSTRATEGY_H
class ContentLengthStrategy {
    public:
        static int IDENTITY;
        static int CHUNKED;
        virtual long determineLength(HttpMessage *) throw(HttpException) = 0;
        virtual ~ContentLengthStrategy() { }
};
#endif
