#include "HttpException.h"
#ifndef CONNROUTEPARAMBEAN_H
#include "ConnRouteParamBean.h"
#endif
ConnRouteParamBean::ConnRouteParamBean(HttpParams *params) : HttpAbstractParamBean(params) {
}
void ConnRouteParamBean::setDefaultProxy (HttpHost *defaultProxy) {
    params->setParameter(ConnRoutePNames::DEFAULT_PROXY, defaultProxy);
}
void ConnRouteParamBean::setLocalAddress (InetAddress* address) {
    params->setParameter(ConnRoutePNames::LOCAL_ADDRESS, address);
}
void ConnRouteParamBean::setForcedRoute(HttpRoute *route) {
    params->setParameter(ConnRoutePNames::FORCED_ROUTE, route);
}
