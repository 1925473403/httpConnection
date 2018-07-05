#include "HttpException.h"
#ifndef SOCKETHTTPSERVERCONNECTION_H
#include "SocketHttpServerConnection.h"
#endif
SocketHttpServerConnection::SocketHttpServerConnection() {
}
SessionInputBuffer* SocketHttpServerConnection::createHttpDataReceiver(Socket *sock, int buffersize, HttpParams *params) throw (IOException) {
    return new SocketInputBuffer(sock, buffersize, params);
}
SessionOutputBuffer* SocketHttpServerConnection::createHttpDataTransmitter(Socket *sock, int buffersize, HttpParams *params) throw (IOException) {
    return new SocketOutputBuffer(sock, buffersize, params);
}
void SocketHttpServerConnection::bind(Socket *sock, HttpParams *params) throw (IOException) {
    if (socket == NULL) throw IllegalArgumentException("Socket may not be null");
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    socket = sock;
    int buffersize = HttpConnectionParams::getSocketBufferSize(params);
    init(createHttpDataReceiver(socket, buffersize, params), createHttpDataTransmitter(socket, buffersize, params), params);
    open = true;
}
InetAddress* SocketHttpServerConnection::getLocalAddress() {
    if (socket != NULL) socket->getLocalAddress();
    return NULL;
}
int SocketHttpServerConnection::getLocalPort() {
    if (socket != NULL) return socket->getLocalPort();
    return -1;
}
InetAddress* SocketHttpServerConnection::getRemoteAddress() {
    if (socket != NULL) return socket->getInetAddress();
    return -1;
}
int SocketHttpServerConnection::getRemotePort() {
    if (socket != NULL) return socket->getPort();
    return -1;
}
void SocketHttpServerConnection::setSocketTimeout(int timeout) {
    assertOpen();
    if (socket != NULL) {
        try {
            socket->setSoTimeout(timeout);
        } catch (const SocketException &ex) { }
    }
}
int SocketHttpServerConnection::getSocketTimeout() {
    if (socket != NULL) {
        try {
            return socket->getSoTimeout();
        } catch (const SocketException &ex) { }
    }
    return -1;
}
void SocketHttpServerConnection::shutdown() throw (IOException) {
    open = false;
    Socket *tmpSocket = socket;
    if (tmpSocket != NULL) tmpSocket->close();
}
void SocketHttpServerConnection::close() throw (IOException) {
    if (!open) return;
    open = false;
    doFlush();
    try {
        socket->shutdownOutput();
    } catch (const IOException &ex) { }
    try {
        socket->shutdownInput();
    } catch (const IOException &ex) { }
    socket->close();
}
