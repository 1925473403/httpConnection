#include "HttpException.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <pthread.h>
#include "NameResolver.h"
#include "InetSocketAddress.h"
#include "SocketImpl.h"
#include "OutputStream.h"
#include "InputStream.h"
#include "AbstractPlainSocketImpl.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "DualStackPlainSocketImpl.h"
#ifndef SOCKET_H
#include "Socket.h"
#endif
Socket::Socket() { 
    setImpl();
}
Socket::~Socket() { impl->unref(); }
Socket::Socket(SocketImpl *i)  {
    impl = i;
    if (impl != NULL) 
        impl->setSocket(this);
}
Socket::Socket(std::string &host, int port) :
    Socket(((host.length() != 0) ? new InetSocketAddress(host, port) : new InetSocketAddress("localhost", port)), NULL, true)  {
}
Socket::Socket(InetAddress *addr, int port) :
    Socket(((addr != NULL)? new InetSocketAddress(addr, port) : 0), NULL, true)  {
}
Socket::Socket(std::string host, int port, InetAddress *localAddr, int localPort) :
    Socket(((host.length() != 0)?new InetSocketAddress(host, port) : new InetSocketAddress("localhost", port)), new InetSocketAddress(localAddr, localPort), true)  {
}
Socket::Socket(InetAddress* addr, int port, InetAddress *localAddr, int localPort) :
    Socket(((addr != NULL)? new InetSocketAddress(addr, port) : 0), new InetSocketAddress(localAddr, localPort), true) {
}
Socket::Socket(std::string host, int port, bool stream) :
    Socket(((host.length() != 0)?new InetSocketAddress(host, port):new InetSocketAddress("localhost", port)), NULL, stream) {
}
Socket::Socket(InetAddress* addr, int port, bool stream) :
    Socket(((addr != NULL)? new InetSocketAddress(addr, port):0), NULL, stream) {
}
Socket::Socket(InetSocketAddress *addr, InetSockAddr *localaddr, bool stream) {
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

void Socket::postAccept() {
    connected = true;
    created = true;
    bound = true;
}

void Socket::setImpl() {
    impl = new DualStackPlainSocketImpl(true);
    if (impl != NULL) impl->setSocket(this);
}
SocketImpl *Socket::getImpl() {
    if (!created) createImpl(true);
    return impl;
}
void Socket::connect(InetSocketAddress *endpoints) {
    connect(endpoints, 0);
}
void Socket::connect(InetSocketAddress *endpoint, int timeout) {
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

void Socket::bind(InetSocketAddress *bindpoint) {
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
InetSocketAddress *Socket::getRemoteSocketAddress() {
    if (!isConnected()) return NULL;
    return new InetSocketAddress(getInetAddress(), getPort());
}
InetSocketAddress *Socket::getLocalSocketAddress() {
    if (!isBound()) return NULL;
     return new InetSocketAddress(getLocalAddress(), getLocalPort());
}
InputStream* Socket::getInputStream() throw (IOException) {
    if (isClosed()) throw SocketException("Socket is closed");
    if (!isConnected()) throw SocketException("Socket is not connected");
    if (isInputShutdown()) throw SocketException("Socket input is shutdown");
    Socket *s = this;
    InputStream *in = NULL;
    in = impl->getInputStream();
    return in;
}
OutputStream* Socket::getOutputStream() throw (IOException){
    if (isClosed()) throw SocketException("Socket is closed");
    if (!isConnected()) throw SocketException("Socket is not connected");
    if (isOutputShutdown()) throw SocketException("Socket output is shutdown");
    Socket *s = this;
    OutputStream *on = NULL;
    on = impl->getOutputStream();
    return on;
}

bool Socket::getReuseAddress() throw (SocketException){
    if (isClosed()) throw SocketException("Socket is closed");

}

void Socket::close() throw (IOException) {
    {
        Lock l(closeLock);
        if (isClosed()) return;
        if (created) impl->close();
        closed = true;
    }
}

void Socket::shutdownInput() throw (IOException) {
    if (isClosed()) throw SocketException("Socket is closed");
    if (!isConnected()) throw SocketException("Socket is not connected");
    if (isInputShutdown()) throw SocketException("Socket input is already shutdown");
    getImpl()->shutdownInput();
    shutIn = true;
}

void Socket::shutdownOutput() throw (IOException) {
    if (isClosed()) throw SocketException("Socket is closed");
    if (!isConnected()) throw SocketException("Socket is not connected");
    if (isOutputShutdown()) throw SocketException("Socket output is already shutdown");
    getImpl()->shutdownOutput();
    shutOut = true;
}

std::string Socket::toString() {
    try {
        if (isConnected()) {
            stringstream ss;
            ss << "Socket[addr=" << getImpl()->getInetAddress() << ",port=" << getImpl()->getPort() << ",localport=" << getImpl()->getLocalPort() << "]";
            return ss.str();
        }
    } catch (const SocketException &e) {
    }
    return "Socket[unconnected]";
}

bool Socket::isClosed() {
    Lock l(closeLock);
    return closed;
}

bool Socket::isInputShutdown() { return shutIn; }
bool Socket::isOutputShutdown() { return shutOut; }
bool Socket::isBound() { return bound || oldImpl; }
bool Socket::isConnected() { return connected || oldImpl; }
