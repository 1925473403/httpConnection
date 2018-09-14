#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <pthread.h>
#include "HttpException.h"
#include "SocketImpl.h"
#include "NameResolver.h"
#include "InetSocketAddress.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "AbstractPlainSocketImpl.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#ifndef DUALSTACKPLAINSOCKETIMPL_H
#include "DualStackPlainSocketImpl.h"
#endif
DualStackPlainSocketImpl::DualStackPlainSocketImpl(bool exclBind) {
    fd = -1;
    exclusiveBind = exclBind;
}

DualStackPlainSocketImpl::DualStackPlainSocketImpl(int f, bool exclBind) {
    fd = f;
    exclusiveBind = exclBind;
}

void DualStackPlainSocketImpl::socketCreate(bool stream) throw(IOException) {
    int newfd = -1;
    if (stream)
        newfd = ::socket(AF_INET, SOCK_STREAM, 0);
    else
        newfd = ::socket(AF_INET, SOCK_DGRAM, 0);
    setFileDescriptor(newfd);
}

void DualStackPlainSocketImpl::socketConnect(InetAddress *address, int port, int timeout) throw (IOException) {
    int nativefd = getFileDescriptor();
    InetSocketAddress isa(address, port);
    sockaddr_in addr = isa.getSockAddress();
    if (::connect(nativefd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0) throw SocketException("Error connecting");
}

void DualStackPlainSocketImpl::socketBind(InetAddress *address, int port) throw(IOException) {
    int nativefd = getFileDescriptor();
    InetSocketAddress isa(address, port);
    sockaddr_in addr = isa.getSockAddress();
    if (::bind(nativefd, (struct sockaddr *)&addr, sizeof( struct sockaddr_in)) < 0) throw SocketException("Error binding");
}

void DualStackPlainSocketImpl::socketListen(int backlog) throw(IOException) {
    int nativefd = getFileDescriptor();
    if (::listen(nativefd, backlog) < 0) throw SocketException("Error listening");
}

void DualStackPlainSocketImpl::socketAccept(SocketImpl *s) throw(IOException) {
    if (s == NULL) throw NullPointerException("socket is null");
    int nativefd = getFileDescriptor();
    struct sockaddr_in cli_addr;
    unsigned int clilen = sizeof(cli_addr);
    int newfd =  ::accept(nativefd, (struct sockaddr *) &cli_addr, &clilen);
    if (newfd < 0) throw SocketException("Error on accept");
    s->setPort(ntohl(cli_addr.sin_port));
    s->setLocalPort(localport);
    s->setFileDescriptor(newfd);
    char clientip[32] = { 0 };
    strcpy(clientip, inet_ntoa(cli_addr.sin_addr));
    s->setAddress(new InetAddress((const char *)clientip));
}

int DualStackPlainSocketImpl::socketAvailable() throw(IOException) {
    return -1;
}

void DualStackPlainSocketImpl::socketClose0(bool useDeferredClose) throw(IOException) {
    int nativefd = getFileDescriptor();
    if (nativefd == -1) throw SocketException("Socket closed");
    setFileDescriptor(-1);
    if (::close(nativefd) < 0) throw SocketException("Socket Close exception");
    nativefd = -1;
}

void DualStackPlainSocketImpl::socketShutdown(int howto) throw(IOException) {
    int nativefd = getFileDescriptor();
    if (nativefd == -1) throw SocketException("Socket closed");
    if (::shutdown(nativefd, howto) < 0) throw SocketException("Socket shutdown exception");
}

void DualStackPlainSocketImpl::socketSendUrgentData(int data) throw(IOException) {
    unsigned char d[sizeof(int) + 1];
    int nativefd = getFileDescriptor();
    data = htonl(data);
    for (int i = 0; i < sizeof(int); i++)
        d[i] = data & (1 << (sizeof(int) - i + 1));
    if (::write(nativefd, d, sizeof(int)) < 0) throw SocketException("Socket Write Error");
}

