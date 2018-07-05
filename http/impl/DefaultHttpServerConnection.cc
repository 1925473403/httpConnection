#include "HttpException.h"
#ifndef DEFAULTHTTPSERVERCONNECTION_H
#include "DefaultHttpServerConnection.h"
#endif
DefaultHttpServerConnection::DefaultHttpServerConnection() {
}
void DefaultHttpServerConnection::bind(Socket *sock, HttpParams* params) throw (IOException) {
    if (socket == NULL) throw IllegalArgumentException("Socket may not be null");
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    assertNotOpen();
    socket->setTcpNoDelay(HttpConnectionParams::getTcpNoDelay(params));
    socket->setSoTimeout(HttpConnectionParams::getSoTimeout(params));
    int linger = HttpConnectionParams::getLinger(params);
    if (linger >= 0) socket->setSoLinger(linger > 0, linger);
    SocketHttpServerConnection::bind(socket, params);
}
std::string DefaultHttpServerConnection::toString() {
    CharArrayBuffer buffer(65);
    buffer.append("[");
    if (isOpen()) buffer.append(getRemotePort());
    else buffer.append("closed");
    buffer.append("]");
    return buffer.toString();
}
