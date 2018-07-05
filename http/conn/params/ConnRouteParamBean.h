#include "HttpException.h"
#ifndef CONNROUTEPARAMBEAN_H
#define CONNROUTEPARAMBEAN_H
class ConnRouteParamBean : public HttpAbstractParamBean {
    public:
        ConnRouteParamBean(HttpParams *params);
        void setDefaultProxy (HttpHost*);
        void setLocalAddress (InetAddress *);
        void setForcedRoute(HttpRoute *);
};
#endif
