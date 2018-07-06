#include "HttpException.h"
#ifndef CONNPERROUTEBEAN_H
#define CONNPERROUTEBEAN_H
class ConnPerRouteBean : public ConnPerRoute {
    private:
        std::unordered_map<HttpRoute*, int> maxPerHostMap;
        int defaultMax;
    public:
        static int DEFAULT_MAX_CONNECTIONS_PER_ROUTE;
        ConnPerRouteBean(int defaultM);
        ConnPerRouteBean();
        int getDefaultMax();
        void setDefaultMaxPerRoute(int max);
        void setMaxForRoute(HttpRoute* route, int max);
        int getMaxForRoute(HttpRoute* route);
        void setMaxForRoutes(std::unordered_map<HttpRoute*, int> &map);
};
#endif
