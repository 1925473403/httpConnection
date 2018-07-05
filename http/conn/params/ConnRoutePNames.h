#include "HttpException.h"
#ifndef CONNROUTEPNAMES_H
#define CONNROUTEPNAMES_H
class ConnRoutePNames {
    ConnRoutePNames() { }
    public:
        static std::string DEFAULT_PROXY;
        static std::string LOCAL_ADDRESS;
        static std::string FORCED_ROUTE;
};
#endif
