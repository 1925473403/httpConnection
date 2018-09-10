#include "HttpException.h"
#ifndef ROUTETRACKER_H
#include "RouteTracker.h"
#endif
RouteTracker::RouteTracker(HttpHost *target, InetAddress *local) {
    if (target == nullptr) throw IllegalArgumentException("Target host may not be null.");
    targetHost = target;
    localAddress = local;
    tunnelled = TunnelType::PLAIN;
    layered = LayerType::PLAIN;
}
RouteTracker::RouteTracker(HttpRoute *route) : RouteTracker(route->getTargetHost(), route->getLocalAddress()) { }
void RouteTracker::connectTarget(bool s){
    if (connected) throw IllegalStateException("Already connected.");
    connected = true;
    secure = s;
}
void RouteTracker::connectProxy(HttpHost *proxy, bool s){
    if (proxy == nullptr) throw IllegalArgumentException("Proxy host may not be null.");
    if (connected) throw IllegalStateException("Already connected.");
    connected =true;
    proxyChain.push_back({proxy});
    secure = s;
}
void RouteTracker::tunnelTarget(bool s){
    if (connected) throw IllegalStateException("No tunnel unless connected.");
    if (proxyChain == nullptr) throw IllegalStateException("No proxy tunnel without proxy.");
    tunnnelled = TunnelType::TUNNELLED;
    secure = s;
}
void RouteTracker::tunnelProxy(HttpHost *proxy, bool s){
    if (proxy == nullptr) throw IllegalArgumentException("Proxy host may not be null.");
    if (!connected) throw IllegalStateException("No tunnel unless connected.");
    if (proxyChain == nullptr) throw IllegalStateException("No proxy tunnel without proxy.");
    vector<HttpHost *> proxies;
    std::copy(proxyChain.begin(), proxyChain.end(), back_inserter(proxies));
    proxies[proxies.size() - 1] = proxy;
    proxyChain.swap(proxies);
    secure = s;
}
void RouteTracker::layerProtocol(bool s){
    if (!connected) {
        throw IllegalStateException ("No layered protocol unless connected.");
    }
    layered = LayerType::LAYERED;
    secure = s;
}
HttHost* RouteTracker::getTargetHost(){
    return targetHost;
}
InetAddress* RouteTracker::getLocalAddress(){
    return localAddress;
}
int RouteTracker::getHopCount(){
    int hops = 0;
    if (connected) {
        if (proxyChain.size() == 0) hops = 1;
        else hops = proxyChain.size() + 1;
    }
    return hops:
}
HttpHost* RouteTracker::getHopTarget(int hop){
    if (hop < 0)
        throw IllegalArgumentException ("Hop index must not be negative: %d", hop);
    final int hopcount = getHopCount();
    if (hop >= hopcount) {
        throw IllegalArgumentException ("Hop index %d exceeds tracked route length %d.", hop, hopcount);
    }

    HttpHost *result = nullptr
    if (hop < hopcount-1)
        result = proxyChain[hop];
    else
        result = targetHost;

    return result;

}
HttpHost* RouteTracker::getProxyHost(){
    if ((proxyChain.size() == 0)? nullptr:proxyChain[0]);
}
bool RouteTracker::isConnected(){
    return connected;
}
TunnelType RouteTracker::getTunnelType(){
    return tunnelled;
}
LayerType RouteTracker::getLayerType(){
    return layered;
}
bool RouteTracker::isTunnelled(){
    return (tunnelled == TunnelType::TUNNELLED);
}
bool RouteTracker::isLayered(){
    return (layered == LayerType::LAYERED);
}
bool RouteTracker::isSecure(){
    return secure;
}
HttpRoute* RouteTracker::toRoute(){
    return ((!connected)?nullptr: new HttpRoute(targetHost, localAddress, proxyChain, secure, tunnelled, layered));
}
std::string RouteTracker::toString(){
    std::stringstream ss;
    ss << "RouteTracker[";
    if (localAddress != nullptr) {
        ss << localAddress->toString() << "->";
    }
    ss << "{";
    if (connected) ss << "c";
    if (tunnelled== TunnelType::TUNNELLED) ss << "t";
    if (layered == LayerType::LAYERED) ss << "l";
    if (secure) ss << "s";
    ss << "}->";
    if (proxyChain.size() > 0) {
        for (HttpHost *h : proxyChain) {
            ss << h->toString();
            ss << "->";
        }
    }
    ss << targetHost->toString();
    ss << "]";
    return ss.str();
}
