#ifndef SOCKET_H
#include "Socket.h"
#endif
Socket::Socket() { 
    setImpl();
}
Socket::~Socket() { delete impl; }
Socket::Socket(SocketImpl *i) {
    impl = i;
    if (impl != NULL) 
        impl->setSocket(this);
}
Socket::Socket(std::string host, int port) :
    Socket(((host.length() != 0) ? new InetSockAddress(host, port) : new InetSockAddress("localhost", port)), NULL, true) {
}
Socket::Socket(InetAddress *addr, int port) :
    Socket(((addr != NULL)? new InetSockAddress(addr, port) : 0), NULL, true) {
}
Socket::Socket(std::string host, int port, InetAddress *localAddr, int localPort) :
    Socket(((host.length() != 0)?new InetSocketAddress(host, port) : new InetSocketAddress("localhost", port)), new InetSocketAddress(localAddr, localPort), true) {
}
Socket::Socket(InetAddress* addr, int port, InetAddress *localAddr, int localPort) :
    Socket(((addr != NULL)? new InetSockAddress(addr, port) : 0), new InetSocketAddress(localAddr, localPort), true) {
}
Socket::Socket(std::string host, int port, bool stream) :
    Socket(((host.length() != 0)?new InetSocketAddress(host, port):new InetSockAddress("localhost", port)), NULL, stream) {
}
Socket::Socket(InetAddress* addr, int port, bool stream) :
    Socket(((addr != NULL)? new InetSockAddress(addr, port):0), NULL, stream) {
}
Socket::Socket(InetSockAddress *addr, InetSockAddr *localaddr, bool stream) {
    setImpl();
    if (addr == NULL) throw NullPointerException();
    try {
        createImpl(stream);
        if (localaddr != NULL) bind(localaddr);
        connect(addr);
    } catch (const IOException &e) {
        try {
            close();
        } catch (const IOException &ce) {
        }
        throw e;
    }
}
void Socket::createImpl(bool stream) {
    if (impl == NULL) setImpl();
    try {
        impl->create(stream);
        created = true;
    } catch (const IOException &e) {
        throw SocketException(e.what());
    }
}

void Socket::setImpl() {
    impl = new SocksSocketImpl();
    if (impl != NULL) impl->setSocket(this);
}
SocketImpl *Socket::getImpl() {
    if (!created) createImpl(true);
    return impl;
}
void Socket::connect(InetSockAddress *endpoints) {
    connect(endpoints, 0);
}
void Socket::connect(InetSockAddress *endpoint, int timeout) {
    if (endpoint == NULL) throw IllegalArgumentException("connect: The address can't be null");
    if (timeout < 0) IllegalArgumentException("connect: timeout can't be negative");
    if (isClosed()) throw SocketException("Socket is closed");
    if (isConnected()) throw SocketException("already connected");
    InetAddress *addr = endpoint->getAddress();
    int port = endpoint->getPort();
    if (!created) createImpl(true);
    if (!oldimpl) impl->connect(endpoint, timeout);
    else if (timeout == 0) {
        impl->connect(addr, port);
    } else throw UnsupportedOperationException("SocketImpl.connect(addr, timeout)");
    connected = true;
    bound = true;
}

void Socket::bind(InetSockAddress *bindpoint) {
    if (isClosed()) throw SocketException("Socket is closed");
    if (!oldImpl && isBound()) throw SocketException("Already bound");
    if (bindpoint == NULL) bindpoint = new InetSocketAddress(0);
    InetAddress *addr = bindpoint->getAddress();
    getImpl()->bind(addr, port);
    bound = true;
}

void Socket::postAccept() {
    connected = true;
    created = true;
    bound = true;
}
void Socket::setCreated() { created = true; }
void Socket::setBound() { bound = true; }
void Socket::setConnected() { connected = true; }
int Socket::getPort() {
    if (!isConnected()) return 0;
    try {
        return getImpl()->getPort();
    } catch (const SocketException &e) {
    }
    return -1;
}
InetAddress* Socket:: getLocalAddress() {
    if (!isBound()) return InetAddress::anyLocalAddress();
    InetAddress* in = NULL;
    try {
        in = getImpl()->getOption(SocketOptions::SO_BINDADDR);
        if (in->isAnyLocalAddress()) in = InetAddress::anyLocalAddress();
    } catch (...) {
        in = InetAddress::anyLocalAddress();
    }
    return in;
}
InetAddress *Socket::getInetAddress() {
    if (!isConnected()) return NULL;
    try {
        return getImpl()->getInetAddress();
    } catch (const SocketException &e) { }
    return NULL;
}
int Socket::getLocalPort() {
    if (!isBound()) return -1;
    try {
        return getImpl()->getLocalPort();
    } catch (const SocketException &e) { }
    return -1;
}
InetSockAddress *Socket::getRemoteSocketAddress() {
    if (!isConnected()) return NULL;
    return new InetSockAddress(getInetAddress(), getPort());
}
InetSockAddress *Socket::getLocalSocketAddress() {
    if (!isBound()) return NULL;
     return new InetSockAddress(getLocalAddress(), getLocalPort());
}
InputStream* Socket::getInputStream() {
    if (isClosed()) throw SocketException("Socket is closed");
    if (!isConnected()) throw SocketException("Socket is not connected");
    if (isInputShutdown()) throw SocketException("Socket input is shutdown");
    Socket *s = this;
    InputStream in = NULL;
    in = impl->getInputStream();
    return in;
}
OutputStream* Socket::getOutputStream() {
    if (isClosed()) throw SocketException("Socket is closed");
    if (!isConnected()) throw SocketException("Socket is not connected");
    if (isOutputShutdown()) throw SocketException("Socket output is shutdown");
    Socket *s = this;
    OutputStream *on = NULL;
    on = impl->getOutputStream();
    return on;
}
