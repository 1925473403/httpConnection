#include "HttpException.h"
#ifndef CONNMANAGERPARAMS_H
#include "ConnManagerParams.h"
#endif
int ConnManagerParams::DEFAULT_MAX_TOTAL_CONNECTIONS = 20;
ConnPerRoute *ConnManagerParams::DEFAULT_CONN_PER_ROUTE = new ConnPerRouteBean();
long ConnManagerParams::getTimeout(HttpParams* params) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    return params->getLongParameter(ConnManagerPNames::TIMEOUT, 0);
}
void ConnManagerParams::setTimeout(HttpParams* params, long timeout) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params->setLongParameter(ConnManagerPNames::TIMEOUT, timeout);
}
void ConnManagerParams::setMaxConnectionsPerRoute(HttpParams* params, ConnPerRoute* connPerRoute) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params->setParameter(ConnManagerPNames::MAX_CONNECTIONS_PER_ROUTE, connPerRoute);
}
ConnPerRoute* ConnManagerParams::getMaxConnectionsPerRoute(HttpParams* params) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    ConnPerRoute *connPerRoute = type_cast<ConnPerRoute *>(params->getParameter(ConnManagerPNames::MAX_CONNECTIONS_PER_ROUTE));
    if (connPerRoute == NULL) connPerRoute = &(ConnManagerParams::DEFAULT_CONN_PER_ROUTE);
    return connPerRoute;
}
void ConnManagerParams::setMaxTotalConnections(HttpParams* params, int maxTotalConnections) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params->setIntParameter(ConnManagerPNames::MAX_TOTAL_CONNECTIONS, maxTotalConnections);
}
int ConnManagerParams::getMaxTotalConnections(HttpParams* params) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    return params->getIntParameter(ConnManagerPNames::MAX_TOTAL_CONNECTIONS, ConnPerRouteBean::DEFAULT_MAX_TOTAL_CONNECTIONS);
}
