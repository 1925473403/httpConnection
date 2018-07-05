#include "HttpException.h"
#ifndef NOCONNECTIONREUSESTRATEGY_H
#define NOCONNECTIONREUSESTRATEGY_H
class NoConnectionReuseStrategy : public ConnectionReuseStrategy {
    public:
        bool keepAlive(HttpResponse *response, HttpContext *context);
};
#endif
