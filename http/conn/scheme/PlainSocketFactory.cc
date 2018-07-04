#include "HttpException.h"
#include "'HttpConnectionParams.h"
#include "InetSockAddress.h"
#include "SocketFactory.h"
#include "Socket.h"
#ifndef PLAINSOCKETFACTORY_H
#include "PlainSocketFactory.h"
#endif
PlainSocketFactory PlainSocketFactory::DEFAULT_FACTORY;
PlainSocketFactory* PlainSocketFactory::getSocketFactory() {
    return &DEFAULT_FACTORY;
}
void PlainSocketFactory::unref() {
    if (this == &PlainSocketFactory::DEFAULT_FACTORY) return;
    delete this;
}
PlainSocketFactory::PlainSocketFactory() {
}
Socket *PlainSocketFactory::createSocket() {
    return new Socket();
}
Socket *PlainSocketFactory::connectSocket(Socket *sock, std::string host, int port, InetAddress *localAddress, int localPort, HttpParams *params) throw (IOException) {
    if (host.length() == 0) throw IllegalArgumentException("Target host may not be null.");
    if (params == NULL) throw  IllegalArgumentException("Parameters may not be null.");
    if (sock == NULL) sock = createSocket();
    if (localAddress != NULL || localPort > 0) {
        if (localPort < 0) localPort = 0;
        InetSocketAddress *isa = new InetSocketAddress(localAddress, port);
        sock->bind(isa);
    }
    int timeout = HttpConnectionParams::getConnectionTimeout(params);
    InetSocketAddress *remoteAddress = NULL;
    remoteAddress = new InetSocketAddress(host, port);
    try {
        sock->connect(remoteAddress, timeout);
    } catch (const SocketTimeoutException &ex) {
        stringstream ss;
        ss << "Connect to " << remoteAddress << " timed out";
        throw ConnectTimeoutException(ss.str().c_str());
    }
    return sock;
}
bool PlainSocketFactory::isSecure(Socket *sock) {
    if (sock == NULL) throw IllegalArgumentException("Socket may not be null.");
    if (sock->isClosed()) throw IllegalArgumentException("Socket is closed.");
    return false;
}
