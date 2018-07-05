#include "HttpException.h"
#ifndef CONNROUTEPARAMS_H
#define CONNROUTEPARAMS_H
class ConnRouteParams : public ConnRoutePNames {
    ConnRouteParams() { }
    public:
    static HttpHost NO_HOST;
    static HttpRoute NO_ROUTE;
    static HttpHost* getDefaultProxy(HttpParams *params);
    static void setDefaultProxy(HttpParams *params, HttpHost *proxy);
    static HttpRoute *getForcedRoute(HttpParams *params);
    static void setForcedRoute(HttpParams *params, HttpRoute *route);
    static InetAddress* getLocalAddress(HttpParams *params);
    static void setLocalAddress(HttpParams *params, InetAddress* local);
};
#endif
