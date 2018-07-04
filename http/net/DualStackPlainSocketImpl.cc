#include "HttpException.h"
#ifndef DUALSTACKPLAINSOCKETIMPL_H
#include "DualStackPlainSocketImpl.h"
#endif
DualStackPlainSocketImpl::DualStackPlainSocketImpl(bool exclBind) {
    fd = -1;
    exclusiveBind = exclBind;
}

DualStackPlainSocketImpl::DualStackPlainSocketImpl(int fd, bool exclBind) {
    int fd = fd;
    exclusiveBind = exclBind;
}

void DualStackPlainSocketImpl::socketCreate(bool stream) throw(IOException) {
    if (fd == -1) throw SocketException("Socket closed");

}

void DualStackPlainSocketImpl::socketConnect(InetAddress *address, int port, int timeout) {
}

void DualStackPlainSocketImpl::socketBind(InetAddress *address, int port) throw(IOException) {
}

void DualStackPlainSocketImpl::socketListen(int backlog) throw(IOException) {
}

void DualStackPlainSocketImpl::socketAccept(SocketImpl s) throw(IOException) {
}

void DualStackPlainSocketImpl::socketClose0(bool useDeferredClose) throw(IOException) {
}

void DualStackPlainSocketImpl::socketShutdown(int howto) throw(IOException) {
}
 
void DualStackPlainSocketImpl::socketSendUrgentData(int data) throw(IOException) {
}
