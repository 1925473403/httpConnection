#include "HttpException.h"
#ifndef CONNPERROUTEBEAN_H
#include "ConnPerRouteBean.h"
#endif
int ConnPerRouteBean::DEFAULT_MAX_CONNECTIONS_PER_ROUTE = 2;
ConnPerRouteBean::ConnPerRouteBean(int defaultM) {
    setDefaultMaxPerRoute(defaultM);
}
ConnPerRouteBean::ConnPerRouteBean() : ConnPerRouteBean(ConnPerRouteBean::DEFAULT_MAX_CONNECTIONS_PER_ROUTE) {
}
int ConnPerRouteBean::getDefaultMax() {
    return defaultMax;
}
void ConnPerRouteBean::setDefaultMaxPerRoute(int max) {
    if (max < 1) throw IllegalArgumentException ("The maximum must be greater than 0.");
    defaultMax = max;
}
void ConnPerRouteBean::setMaxForRoute(HttpRoute* route, int max) {
    if (route == NULL) throw IllegalArgumentException("HTTP route may not be null.");
    if (max < 1) throw IllegalArgumentException ("The maximum must be greater than 0.");
    maxPerHostMap.insert(std::make_pair(route, max));
}
int ConnPerRouteBean::getMaxForRoute(HttpRoute* route) {
    if (route == NULL) throw IllegalArgumentException("HTTP route may not be null.");
    int max = -1;
    std::unordered_map<HttpRoute*, int>::iterator it = maxPerHostMap.find(route);
    if (it != maxPerHostMap.end()) max = it->second;
    if (max != -1) return max;
    return defaultMax;
}
void ConnPerRouteBean::setMaxForRoutes(std::unordered_map<HttpRoute*, int> &map) {
    if (map.size() == 0) return;
    for (std::unordered_map<HttpRoute*, int>::iterator it = maxPerHostMap.begin(); it != maxPerHostMap.end(); it++) {
        HttpRoute *r = it->first;
        if (r != NULL) delete r;
    }
    maxPerHostMap.clear();
    for (std::unordered_map<HttpRoute*, int>::iterator it = map.begin(); it != map.end(); it++) {
        maxPerHostMap.insert(std::make_pair(it->first, it->second));
    }
}
