#include "HttpException.h"
#ifndef CONNMANAGERPARAMBEAN_H
#include "ConnManagerParamBean.h"
#endif
ConnManagerParamBean::ConnManagerParamBean(HttpParams *params) : HttpAbstractParamBean(params) {
}
void ConnManagerParamBean::setTimeout (long timeout) {
    params->setLongParameter(ConnManagerPNames::TIMEOUT, timeout);
}
void ConnManagerParamBean::setMaxTotalConnections (int maxConnections) {
    params->setIntParameter(ConnManagerPNames::MAX_TOTAL_CONNECTIONS, maxConnections);
}
void ConnManagerParamBean::setConnectionsPerRoute(ConnPerRouteBean connPerRoute) {
    params->setParameter(ConnManagerPNames::MAX_CONNECTIONS_PER_ROUTE, connPerRoute);
}
