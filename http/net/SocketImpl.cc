#ifndef "HttpException.h"
#ifndef SOCKETIMPL_H
#include "SocketImpl.h"
#endif
class SocketImpl {
    private:
    protected:
        Socket *socket;
        ServerSocket *serverSocket;
        int port;
        int localport;
        int fd;
        InetAddress *address;
void SocketImpl::socketCreate(bool isServer) throw(IOException) {
    if (isServer) fd = socket(AF_INET, SOCK_STREAM, 0);
    else fd = socket(AF_INET, SOCK_DGRAM, 0);
}
void SocketImpl::socketConnect(InetAddress *address, int port, int timeout) throw (IOException) {
    InetSocketAddress *i = new InetSocketAddress(address, port);
    
}
void SocketImpl::socketBind(InetAddress *address, int port) throw (IOException) {
}
void SocketImpl::socketListen(int count) throw (IOException) {
}
void SocketImpl::socketAccept(SocketImpl *s) throw (IOException) {
}
int SocketImpl::socketAvailable() throw (IOException) {
}
void SocketImpl::socketShutdown(int howto) throw (IOException) {
}
void SocketImpl::socketSendUrgentData(int data) throw (IOException) {
}
