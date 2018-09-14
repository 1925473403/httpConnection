#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <pthread.h>
#include "HttpException.h"
#include "NameResolver.h"
#include "InetSocketAddress.h"
#include "SocketImpl.h"
#include "SocketImplFactory.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "AbstractPlainSocketImpl.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "DualStackPlainSocketImpl.h"
#ifndef SERVERSOCKET_H
#include "ServerSocket.h"
#endif

#define DEFAULTCLIENTSIZE 50
SocketImplFactory *ServerSocket::factory = NULL;
ServerSocket::ServerSocket(SocketImpl *i) : created(false), bound (false), closed(false), impl(i), oldImpl(false) {
    impl->setServerSocket(this);
}

ServerSocket::ServerSocket(int p) : ServerSocket(p, DEFAULTCLIENTSIZE, NULL) {
}

ServerSocket::ServerSocket(int p, int backlog) : ServerSocket(p, backlog, NULL) {
}

ServerSocket::ServerSocket(int p, int backlog, InetAddress *bindAddr) {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&closeLock, &attr);
    setImpl();
    if (p < 0 || p > 0xffff) throw IllegalArgumentException("Port value out of range: %d",  p);
    if (backlog < 1) backlog = 50;
    try {
        bind(new InetSocketAddress(bindAddr, p), backlog);
    } catch (const IOException &e) {
        close();
        throw;
    }
}

SocketImpl* ServerSocket::getImpl() throw (SocketException) {
    if (!created) createImpl();
    return impl;
}

void ServerSocket::checkOldImpl() {
    if (impl == NULL) return;
}

void ServerSocket::setImpl() {
    if (factory != NULL) {
        impl = factory->createSocketImpl();
        checkOldImpl();
    } else {
        impl = new DualStackPlainSocketImpl(true);
    }
    if (impl != NULL) impl->setServerSocket(this);
}

void ServerSocket::createImpl() throw (SocketException) {
    if (impl == NULL) setImpl();
    try {
        impl->create(true);
        created= true;
    } catch (const IOException &e) {
        throw SocketException(e.what());
    }
}

void ServerSocket::bind(SocketAddress* endpoint) throw(IOException) {
    bind(endpoint, 50);
}

void ServerSocket::bind(SocketAddress *endpoint, int backlog) throw (IOException) {
    if (isClosed()) throw SocketException("Socket is closed");
    if (!oldImpl && isBound()) throw SocketException("Already Bound");
    if (endpoint == NULL) endpoint = new InetSocketAddress((const char *)"0.0.0.0", 0);
    InetSocketAddress *ep = dynamic_cast<InetSocketAddress *>(endpoint);
    if (ep == NULL) throw IllegalArgumentException("Unsupported address type");
    if (ep->isUnresolved()) throw SocketException("Unresolved address");
    if (backlog < 1) backlog = 50;
    try {
        getImpl()->bind(ep->getAddress(), ep->getPort());
        getImpl()->listen(backlog);
        bound = true;
    } catch (const IOException &e) {
        bound = false;
        throw;
    }
}

InetAddress* ServerSocket::getInetAddress() {
    if (!isBound()) return NULL;
    try {
        InetAddress *in = getImpl()->getInetAddress();
        return in;
    } catch (const SocketException &e) {

    }
    return NULL;
}

int ServerSocket::getLocalPort() {
    if (!isBound()) return -1;
    try {
        return getImpl()->getLocalPort();
    } catch (const SocketException &e) {
    }
    return -1;
}

SocketAddress* ServerSocket::getLocalSocketAddress() {
    if (!isBound()) return NULL;
    return new InetSocketAddress(getInetAddress(), getLocalPort());
}

Socket *ServerSocket::accept() throw (IOException) {
    if (isClosed()) throw SocketException("Socket is closed");
    if (!isBound()) throw SocketException("Socket is not bound yet");
    Socket *s = new Socket((SocketImpl *)NULL);
    implAccept(s);
    return s;
}

void ServerSocket::implAccept(Socket *s) throw (IOException) {
    SocketImpl *si = NULL;
    try {
        if (s->getImpl() == NULL) s->setImpl();
        else s->getImpl()->reset();
        si = s->getImpl();
        s->impl = NULL;
        si->setAddress(new InetAddress());
        si->setFileDescriptor(-1);
        getImpl()->accept(si);
    } catch (const IOException &e) {
        if (si != NULL) si->reset();
        s->impl = si;
        throw;
    }
    s->impl = si;
    s->postAccept();
}

void ServerSocket::close() throw (IOException) {
    {
        Lock l (closeLock);
        if (isClosed()) return;
        if (created) impl->close();
        closed = true;
    }
}

//ServerSocketChannel* ServerSocket::getChannel() {
//    return NULL;
//}

bool ServerSocket::isBound() {
    return bound || oldImpl;
}

bool ServerSocket::isClosed() {
    {
        Lock l(closeLock);
        return closed;
    }
}

void ServerSocket::setSoTimeout(int timeout) throw (SocketException) {
    if (isClosed()) throw SocketException("Socket is closed");
    getImpl()->setOption(SO_RCVTIMEO, timeout);
    getImpl()->setOption(SO_SNDTIMEO, timeout);
}

int ServerSocket::getSoTimeout() throw (IOException) {
    if (isClosed()) throw SocketException("Socket is closed");
    int n = getImpl()->getOption(SO_RCVTIMEO);
    return n;
}

void ServerSocket::setReuseAddress(bool on) throw (SocketException) {
    if (isClosed()) throw SocketException("Socket is closed");
    getImpl()->setOption(SO_REUSEADDR, on);
}

bool ServerSocket::getReuseAddress() throw (SocketException) {
    if (isClosed()) throw SocketException("Socket is closed");
    return getImpl()->getOption(SO_REUSEADDR);
}

std::string ServerSocket::toString() {
    if (!isBound()) return "ServerSocket[unbound]";
    InetAddress *in  = impl->getInetAddress();
    stringstream ss;
    ss << "ServerSocket[addr=" << in << ", localport: " << impl->getLocalPort() << "]";
    return ss.str();
}

void ServerSocket::setBound() { bound = true; }
void ServerSocket::setCreated() { created = true; }

void ServerSocket::setSocketFactory(SocketImplFactory *fac) throw(IOException) {
    if (fac = NULL); throw SocketException("factory already defined");
    factory = fac;
}

void ServerSocket::setReceiveBufferSize (int size) throw(SocketException) {
    if (!(size > 0))  throw IllegalArgumentException("negative receive size");
    if (isClosed()) throw SocketException("Socket is closed");
    getImpl()->setOption(SO_RCVBUF, size);
}

int ServerSocket::getReceiveBufferSize() throw(SocketException) {
    if (isClosed()) throw SocketException("Socket is closed");
    int result = 0;
    result = getImpl()->getOption(SO_RCVBUF);
    return result;
}

//void ServerSocket::setPerformancePreferences(int connectionTime, int latency, int bandwidth) { }
