#include "HttpException.h"
#ifndef CONNMANAGERPNAMES_H
#define CONNMANAGERPNAMES_H
class ConnManagerPNames {
    ConnManagerPNames() { }
    public:
        static std::string TIMEOUT;
        static std::string MAX_CONNECTIONS_PER_ROUTE;
        static std::string MAX_TOTAL_CONNECTIONS;
};
#endif
