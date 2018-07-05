#include "HttpException.h"
#ifndef CONNROUTEPARAMS_H
#include "ConnRouteParams.h"
#endif
HttpHost NO_HOST("127.0.0.255", 0, "no-host");
HttpRoute NO_ROUTE(&NO_HOST);
HttpHost* ConnRouteParams::getDefaultProxy(HttpParams *params) {
    if (params == NULL) throw IllegalArgumentException("Parameters must not be null.");
    HttpHost *proxy = params->getParameter(ConnRoutePNames::DEFAULT_PROXY);
    if ((proxy != NULL) && NO_HOST.equals(*proxy)) proxy = NULL;
    return proxy;
}
void ConnRouteParams::setDefaultProxy(HttpParams *params, HttpHost *proxy) {
    if (params == NULL) throw IllegalArgumentException("Parameters must not be null.");
    params->setParameter(ConnRoutePNames::DEFAULT_PROXY, proxy);
}
HttpRoute *ConnRouteParams::getForcedRoute(HttpParams *params) {
    if (params == NULL) throw IllegalArgumentException("Parameters must not be null.");
    HttpRoute *proxy = params->getParameter(ConnRoutePNames::FORCED_ROUTE);
    if ((proxy != NULL) && NO_ROUTE.equals(*proxy)) proxy = NULL;
    return proxy;
}
void ConnRouteParams::setForcedRoute(HttpParams *params, HttpRoute *route) {
    if (params == NULL) throw IllegalArgumentException("Parameters must not be null.");
    params->setParameter(ConnRoutePNames::FORCED_ROUTE, route);
}
InetAddress* ConnRouteParams::getLocalAddress(HttpParams *params) {
    if (params == NULL) throw IllegalArgumentException("Parameters must not be null.");
    InetAddress *local = params->getParameter(ConnRoutePNames::LOCAL_ADDRESS);
    return local;
}
void ConnRouteParams::setLocalAddress(HttpParams *params, InetAddress* local) {
    if (params == NULL) throw IllegalArgumentException("Parameters must not be null.");
    params->setParameter(ConnRoutePNames::LOCAL_ADDRESS, local);
}
