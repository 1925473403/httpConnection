#include "HttpException.h"
#include "RefCount.h"
#ifndef CONNECTIONREUSESTRATEGY_H
#define CONNECTIONREUSESTRATEGY_H
class ConnectionReuseStrategy : public RefCount {
    public:
    virtual ~ConnectionReuseStrategy() { }
    virtual bool keepAlive(HttpResponse *response, HttpContext *context) = 0;
};
#endif
