#include "HttpException.h"
#include "HttpHost.h"
#include "InetAddress.h"

#ifndef HTTPROUTE_H
#define "HttpRoute.h"
#endif
HttpRoute::HttpRoute(InetAddress *local, HttpHost *target, vector<HttpHost *> &proxies, bool s, TunnelType t, LayerType l) {
    if (target == NULL) throw IllegalArgumentException ("Target host may not be null.");
    if ((t == TunnelType.TUNNELLED) && (proxies == nullptr)) throw IllegalArgumentException("Proxy required if tunnelled.");
    if (t == nullptr) t = TunnelType.PLAIN;
    if (l == nullptr) l = LayerType.PLAIN;
    targetHost = target;
    localAddress = local;
    proxyChain.swap(proxies);
    secure = s;
    tunnelled = t;
    layered = l;
}
static vector<HttpHost *> HttpRoute::toChain(HttpProxy *h) {
    vector<HttpHost *> res;
    if (h != nullptr) res.push_back(h);
    return res;
}
HttpRoute::HttpRoute(HttpHost *target, InetAddress *local, vector<HttpHost *> &proxies, bool s, TunnelType t, LayerType l):
    HttpRoute(local, target, proxies, s, t, l) { }
HttpRoute::HttpRoute(HttpHost *target, InetAddress *local, HttpHost *proxies, bool s, TunnelType t, LayerType l):
    HttpRoute(local, target, toChain(proxies), s, t, l) { }
HttpRoute::HttpRoute(HttpHost *target, InetAddress *local, bool s) : 
    HttpRoute(local, target, HttpRoute::toChain(nullptr), s, TunnelType::PLAIN, LayerType::PLAIN);
HttpRoute::HttpRoute(HttpHost *target) : 
    HttpRoute(nullptr, target, HttpRoute::toChain(nullptr), false, TunnelType::PLAIN, LayerType::PLAIN);
HttpRoute::HttpRoute(HttpHost *target, InetAddress *local, HttpHost *proxy, bool s) : 
    HttpRoute(nullptr, target, HttpRoute::toChain(proxy), s, (s?TunnelType::TUNNELLED:TunnelType::PLAIN), (s?LayerType::LAYERED:LayerType::PLAIN)) {
    if (proxy == nullptr) throw IllegalArgumentException("Proxy host may not be null.");
}
HttpHost *HttpRoute::getTargetHost() { return targetHost; }
InetAddress *HttpRoute::getLocalAddress() { return localAddress; }
int HttpRoute::getHostCount() { return ((proxyChain.size() == 0)? 1:(proxyChain.size() + 1)); }
HttpHost* HttpRoute::getHopTarget(int hop) {
    if (hop < 0)
        throw IllegalArgumentException ("Hop index must not be negative: %d", hop);
    int hopcount = getHopCount();
    if (hop >= hopcount)
        throw IllegalArgumentException ("Hop index %d exceeds route length %d", hop, hopcount);

    HttpHost* result = nullptr;
    if (hop < hopcount-1) result = proxyChain[hop];
    else result = targetHost;
    return result;
}
HttpHost *HttpRoute::getProxyHost() {
    return ((proxyChain == nullptr)? nullptr : proxyChain[0]);
}
TunnelType HttpRoute::getTunnelType() { return tunnelled; }
bool HttpRoute::isTunnelled() { return (tunnelled == TunnelType::TUNNELLED); }
LayerType HttpRoute::getLayerType() { return layered; }
bool HttpRoute::isSecure() { return secure; }
bool HttpRoute::isLayered() { return (layered == LayerType::LAYERED); }
std::string HttpRoute::toString() {
    std::stringstream ss;
    ss << "HttpRoute[" ;
    if (localAddress != nullptr) ss << localAddress->toString()  << "->";
    ss << "{"
    if (tunnelled == TunnelType::TUNNELLED) ss << "t";
    if (layered == LayerType::LAYERED) ss <<"l";
    if (secure) ss << "s";
    ss << "}->";
    if (proxyChain.size() == 0) {
        for (HttpHost *h : proxyChain) {
            ss << h->toString() << "->";
        }
    }
    ss << targetHost->toString() ;
    ss << "]";
    return ss.str();
}
