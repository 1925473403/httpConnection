#include "HttpException.h"
#ifndef ROUTEINFO_H
#define ROUTEINFO_H
class RouteInfo {
    public:
    enum TunnelType { PLAIN, TUNNELLED };
    enum LayerType { PLAIN, LAYERED };
    virtual ~RouteInfo();
    virtual HttpHost getTargetHost() = 0;
    virtual InetAddress *getLocalAddress() = 0;
    virtual int getHopCount() = 0;
    virtual HttpHost *getHopTarget() = 0;
    virtual HttpHost *getProxyHost() = 0;
    virtual TunnelType getTunnelType() = 0;
    virtual bool isTunnelled() = 0;
    virtual LayerType getLayerType() = 0;
    virtual bool isLayered() = 0;
    virtual bool isSecure() = 0;
};
#endif
