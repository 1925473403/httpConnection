#include "Value.h"
#ifndef SOCKETHTTPCLIENTCONNECTION_H
#include "SocketHttpClientConnection.h"
#endif
SocketHttpClientConnection::SocketHttpClientConnection() { }
SocketHttpClientConnection::~SocketHttpClientConnection() { }
SessionInputBuffer* SocketHttpClientConnection::createSessionInputBuffer(Socket *sock, int, HttpParams*) throw (IOException) {
    return new SocketInputBuffer(sock, buffersize, params);
}
SessionOutputBuffer* SocketHttpClientConnection::createSessionOutputBuffer(Socket *sock, int, HttpParams*) throw (IOException) {
    return new SocketOutputBuffer(sock, buffersize, params);
}
void SocketHttpClientConnection::bind(Socket *sock, HttpParams* params) throw (IOException) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    socket = sock;
    int buffersize = HttpConnectionParams::getSocketBufferSize(params);
    init(createSessionInputBuffer(socket, buffersize, params), createSessionOutputBuffer(socket, buffersize, params), params);
    open = true;
}
InetAddress* SocketHttpClientConnection::getLocalAddress() {
    if (socket != NULL) return socket->getLocalAddress();
    return NULL;
}
int SocketHttpClientConnection::getLocalPort() const {
    if (socket != NULL) return socket->getLocalPort();
    return -1;
}
InetAddress* SocketHttpClientConnection::getRemoteAddress() {
    if (socket != NULL) return socket->getInetAddress();
    return NULL;
}
int SocketHttpClientConnection::getRemotePort() const {
    if (socket != NULL) return socket->getPort();
    return -1;
}
void SocketHttpClientConnection::setSocketTimeout(int timeout) {
    assertOpen();
    if (socket != NULL) {
        try {
            socket->setSoTimeout(timeout);
        } catch (const SocketException &ex) { }
    }
}
int SocketHttpClientConnection::getSocketTimeout() const {
    if (socket != NULL) {
        try {
            return socket->getSoTimeout();
        } catch (const const SocketException &ex) { }
    }
    return -1;
}
void SocketHttpClientConnection::shutdown() throw (IOException) {
    open = false;
    Socket *tmpSocket = socket;
    if (tmpSocket != NULL) tmpSocket->close();
}
void SocketHttpClientConnection::close() throw (IOException) {
    if (!open) return;
    open = false;
    doFlush();
    try {
        try {
            socket->shutdownOutput();
        } catch (const IOException &e) {
        try {
            socket->shutdownInput();
        } catch (const IOException &e) {
        }
    } catch(const UnsupportedOperationException &ignore) {
    }
    socket->close();
}
