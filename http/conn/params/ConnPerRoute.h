#include "HttpException.h"
#ifndef CONNPERROUTE_H
#define CONNPERROUTE_H
class ConnPerRoute {
    public:
        virtual ~ConnPerRoute() { }
        virtual getMaxForRoute(HttpRoute *route) = 0;
};
#endif
