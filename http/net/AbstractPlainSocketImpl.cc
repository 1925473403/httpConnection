#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include "HttpException.h"
#include "SocketImpl.h"
#include "NameResolver.h"
#include "InetSocketAddress.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#ifndef ABSTRACTPLAINSOCKETIMPL_H
#include "AbstractPlainSocketImpl.h"
#endif
#include "Socket.h"

int AbstractPlainSocketImpl::SHUT_RD = 0;
int AbstractPlainSocketImpl::SHUT_WR = 1;
void AbstractPlainSocketImpl::create(bool stream) {
    socketCreate(stream);
}

void AbstractPlainSocketImpl::connect(std::string &host, int p) throw (UnknownHostException, IOException) {
    connect(host.c_str(), p);
}

void AbstractPlainSocketImpl::connect(const char* host, int p) throw (UnknownHostException, IOException) {
    bool connected = false;
    try {
        InetAddress *addr = InetAddress::getByName(host);
        port = p;
        address = addr;
        connectToAddress(address, port, timeout);
        connected = true;
    } catch (...) {
        if (!connected) {
            try {
                close();
            } catch (const IOException &ex) { }
        }
    }
    if (!connected) {
        try {
            close();
        } catch (const IOException &ex) { }
    }
}

void AbstractPlainSocketImpl::connect(InetAddress* addr, int p) throw (IOException) {
    port = p;
    address = addr;
    try {
        connectToAddress(address, port, timeout);
        return;
    } catch (const IOException &ex) {
        close();
        throw;
    }
}

void AbstractPlainSocketImpl::connectToAddress(InetAddress* addr, int p, int t) throw (IOException) {
    if (address->isAnyLocalAddress()) doConnect(InetAddress::getLocalHost(), p, t);
    else doConnect(addr, p, t);
}

void AbstractPlainSocketImpl::doConnect(InetAddress* addr, int port, int timeout) throw (IOException) {
    {
        Lock l(fdLock);
        try {
            acquireFD();
            try {
                socketConnect(address, port, timeout);
                if (closePending) throw SocketException ("Socket closed");
                if (socket != NULL) {
                    socket->setConnected();
                    socket->setBound();
                }
            } catch (...) {
                releaseFD();
                throw;
            }
            releaseFD();
        } catch (const IOException &e) {
            close();
            throw;
        }
    }
}

void AbstractPlainSocketImpl::bind(InetAddress *host, int port) {
    Lock l(fdLock);
    socketBind(host, port);
    if (socket != NULL) socket->setBound();
    if (serverSocket != NULL) serverSocket->setBound();
}

void AbstractPlainSocketImpl::listen(int baclog) {
    socketListen(baclog);
}

void AbstractPlainSocketImpl::accept(SocketImpl *s) {
    acquireFD();
    try {
        socketAccept(s);
    } catch(...) {
        releaseFD();
        throw;
    }
    releaseFD();
}

InputStream *AbstractPlainSocketImpl::getInputStream() {
    Lock l(fdLock);
    if (isClosedOrPending()) throw IOException("Socket Closed");
    if (shut_rd) throw IOException("Socket input is shutdown");
    if (socketInputStream == NULL) socketInputStream = new SocketInputStream(this);
    return socketInputStream;
}



OutputStream *AbstractPlainSocketImpl::getOutputStream() {
    Lock l(fdLock);
    if (isClosedOrPending()) throw IOException("Socket Closed");
    if (shut_wr) throw IOException("Socket output is shutdown");
    if (socketOutputStream == NULL) socketOutputStream = new SocketOutputStream(this);
    return socketOutputStream;
}

int AbstractPlainSocketImpl::available() {
    int n = 0;
    {
        Lock l(fdLock);
        if (isClosedOrPending()) throw IOException("Stream closed.");
        if (isConnectionReset() || shut_rd) return 0;
        try {
            n = socketAvailable();
            if (n == 0 && isConnectionResetPending()) setConnectionReset();
        } catch (const ConnectionResetException& ex) {
            setConnectionResetPending();
            try {
                n = socketAvailable();
                if (n == 0) setConnectionReset();
            } catch (const ConnectionResetException& e) {
            }
        }
    }
    return n;
}

void AbstractPlainSocketImpl::close() {
    {
        Lock l(fdLock);
        if (fd != -1) {
            if (fdUseCount == 0) {
                if (closePending) return;
                closePending = true;
                try {
                    socketPreClose();
                } catch(...) {
                    socketClose();
                    throw;
                }
                socketClose();
                fd = -1;
                return;
            } else {
                if (!closePending) {
                    closePending = true;
                    fdUseCount--;
                    socketPreClose();
                }
            }
        }
    }
}

void AbstractPlainSocketImpl::socketClose() {
    if (fd > 0) ::close(fd);
    fd = -1;
}

void AbstractPlainSocketImpl::reset() {
    if (fd != -1) socketClose();
    fd = -1;
}

AbstractPlainSocketImpl::AbstractPlainSocketImpl() {
    socketInputStream = NULL;
    socketOutputStream = NULL;
    fdUseCount = 0;
    closePending = false;
    shut_rd = false;
    shut_wr = false;
    CONNECTION_NOT_RESET = 0;
    CONNECTION_RESET_PENDING = 1;
    CONNECTION_RESET = 2;
}

void AbstractPlainSocketImpl::shutdownInput() {
    if (fd != -1) {
        socketShutdown(SHUT_RD);
        if (socketInputStream != NULL) instream->setEOF(true);
        shut_rd = true;
    }
}

void AbstractPlainSocketImpl::shutdownOutput() {
    if (fd != -1) {
        socketShutdown(SHUT_WR);
        shut_wr = true;
    }
}

int AbstractPlainSocketImpl::getFileDescriptor() {
}

int AbstractPlainSocketImpl::getPort() {
    return port;
}

InetAddress* AbstractPlainSocketImpl::getInetAddress() {
    return address;
}

int AbstractPlainSocketImpl::getLocalPort() {
    return localport;
}

void AbstractPlainSocketImpl::setOption(int opt, int val) {
}

int AbstractPlainSocketImpl::getOption(int opt) {
}

void AbstractPlainSocketImpl::sendUrgentData (int data) {
    if (fd == -1) throw IOException("Socket Closed");
    socketSendUrgentData (data);
}

int AbstractPlainSocketImpl::acquireFD() {
    Lock l(fdLock);
    fdUseCount++;
    return fd;
}

void AbstractPlainSocketImpl::releaseFD() {
    Lock l(fdLock);
    fdUseCount--;
    if (fdUseCount == -1) {
        if (fd != -1) {
            try {
                socketClose();
            } catch (const IOException e) {
            } catch (...) {
            }
            fd = -1;
        }
    }
}

int AbstractPlainSocketImpl::getTimeout() {
    return timeout;
}

bool AbstractPlainSocketImpl::isConnectionReset() {
    Lock l(resetLock);
    return (resetState == CONNECTION_RESET);
}

bool AbstractPlainSocketImpl::isConnectionResetPending() {
    Lock l(resetLock);
    return (resetState == CONNECTION_RESET_PENDING);
}

void AbstractPlainSocketImpl::setConnectionReset() {
    Lock l(resetLock);
    resetState = CONNECTION_RESET;
}
void AbstractPlainSocketImpl::setConnectionResetPending() {
    Lock l(resetLock);
    if (resetState == CONNECTION_NOT_RESET) resetState = CONNECTION_RESET_PENDING;
}

bool AbstractPlainSocketImpl::isClosedOrPending() {
    Lock l(fdLock);
    if (closePending || (fd == -1)) return true;
    else return false;
}
