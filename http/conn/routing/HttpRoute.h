#include "HttpException.h"
#ifndef HTTPROUTE_H
#define HTTPROUTE_H
class HttpRoute : public RouteInfo {
    private:
    HttpHost *targetHost;
    InetAddress *localAddress;
    vector<HttpHost *> proxyChain;
    TunnelType tunnelled;
    LayerType layered;
    bool secure;
    HttpRoute(InetAddress *local, HttpHost *target, vector<HttpHost *> &proxies, bool s, TunnelType t, LayerType l);
    static vector<HttpHost *> toChain(HttpProxy *h) ;
    protected:
    public:
    HttpRoute(HttpHost *target, InetAddress *local, vector<HttpHost *> &proxies, bool s, TunnelType t, LayerType l);
    HttpRoute(HttpHost *target, InetAddress *local, HttpHost *proxies, bool s, TunnelType t, LayerType l);
    HttpRoute(HttpHost *target, InetAddress *local, bool s) ; 
    HttpRoute(HttpHost *target) ;
    HttpRoute(HttpHost *target, InetAddress *local, HttpHost *proxy, bool s) ;
    HttpHost *getTargetHost();
    InetAddress *getLocalAddress();
    int getHostCount();
    HttpHost* getHopTarget(int hop) ;
    HttpHost *getProxyHost();
    TunnelType getTunnelType();
    bool isTunnelled();
    LayerType getLayerType();
    bool isSecure();
    bool isLayered();
    std::string toString();
};
#endif
