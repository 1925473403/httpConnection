#include "HttpException.h"
#ifndef ROUTETRACKER_H
#define ROUTETRACKER_H
class RouteTracker : public RouteInfo {
    private:
    HttpHost *targetHost;
    InetAddress *localAddress;
    bool connected;
    vector<HttpHost *> proxyChain;
    TunnelType tunnelled;
    LayerType layered;
    bool secure;
    public:
    RouteTracker(HttpHost *target, InetAddress *local) {
        if (target == nullptr) throw IllegalArgumentException("Target host may not be null.");
        targetHost = target;
        localAddress = local;
        tunnelled = TunnelType::PLAIN;
        layered = LayerType::PLAIN;
    }
    RouteTracker(HttpRoute *route);
    void connectTarget(bool secure);
    void connectProxy(HttpHost *proxy, bool s);
    void tunnelTarget(bool s);
    void tunnelProxy(HttpHost *proxy, bool s);
    void layerProtocol(bool s);
    HttHost* getTargetHost();
    InetAddress* getLocalAddress();
    int getHopCount();
    HttpHost* getHopTarget(int hop);
    HttpHost* getProxyHost();
    bool isConnected();
    TunnelType getTunnelType();
    LayerType getLayerType();
    bool isTunnelled();
    bool isLayered();
    bool isSecure();
    HttpRoute* toRoute();
    std::string toString();
};
#endif
