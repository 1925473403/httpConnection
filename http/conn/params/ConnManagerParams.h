#include "HttpException.h"
#ifndef CONNMANAGERPARAMS_H
#define CONNMANAGERPARAMS_H
class ConnManagerParams : public ConnManagerPNames {
    public:
        static int DEFAULT_MAX_TOTAL_CONNECTIONS;
        static long getTimeout(HttpParams* params);
        static void setTimeout(HttpParams* params, long timeout);
        static ConnPerRoute *DEFAULT_CONN_PER_ROUTE;
        static void setMaxConnectionsPerRoute(HttpParams* params, ConnPerRoute* connPerRoute);
        static ConnPerRoute* getMaxConnectionsPerRoute(HttpParams* params);
        static void setMaxTotalConnections(HttpParams* params, int maxTotalConnections);
        static int getMaxTotalConnections(HttpParams* params);
};
#endif
