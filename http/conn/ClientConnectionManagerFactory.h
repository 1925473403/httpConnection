#include "HttpException.h"
#ifndef CLIENTCONNECTIONMANAGERFACTORY_H
#define CLIENTCONNECTIONMANAGERFACTORY_H
class ClientConnectionManagerFactory {
    public:
        virtual ~ClientConnectionManagerFactory() { }
        virtual ClientConnectionManager* newInstance(HttpParams *params, SchemeRegistry* schemeRegistry) = 0;
};
#endif
