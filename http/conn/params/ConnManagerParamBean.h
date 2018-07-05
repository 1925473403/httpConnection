#include "HttpException.h"
#ifndef CONNMANAGERPARAMBEAN_H
#define CONNMANAGERPARAMBEAN_H
class ConnManagerParamBean : public HttpAbstractParamBean {
    public:
        ConnManagerParamBean(HttpParams *params);
        void setTimeout (long timeout);
        void setMaxTotalConnections (int maxConnections);
        void setConnectionsPerRoute(ConnPerRouteBean connPerRoute);
};
#endif
