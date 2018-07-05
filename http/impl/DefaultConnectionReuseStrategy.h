#include "HttpException.h"
#ifndef DEFAULTCONNECTIONREUSESTRATEGY_H
#define DEFAULTCONNECTIONREUSESTRATEGY_H
class DefaultConnectionReuseStrategy : public ConnectionReuseStrategy {
    protected:
        TokenIterator* createTokenIterator(HeaderIterator *hit);
    public:
        DefaultConnectionReuseStrategy();
        bool keepAlive(HttpResponse *response, HttpContext *context);
};
#endif
