#include "HttpException.h"
#include "HttpConnectionParams.h"
#include "HttpParams.h"
#include "Socket.h"
#include "SocketHttpClientConnection.h"
#ifndef DEFAULTHTTPCLIENTCONNECTION_H
#include "DefaultHttpClientConnection.h"
#endif
DefaultHttpClientConnection::DefaultHttpClientConnection() : SocketHttpClientConnection() {
}
void DefaultHttpClientConnection::bind(Socket *socket, HttpParams *params) throw (IOException) {
    if (socket == NULL) throw IllegalArgumentException("Socket may not be null");
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    assertNotOpen();
    socket->setTcpNoDelay(HttpConnectionParams::getTcpNoDelay(params));
    socket->setSoTimeout(HttpConnectionParams::getSoTimeout(params));
    int linger = HttpConnectionParams::getLinger(params);
    if (linger >= 0) socket->setSoLinger(linger > 0, linger);
    SocketHttpClientConnection::bind(socket, params);
}
std::string DefaultHttpClientConnection::toString() {
    CharArrayBuffer buffer(64);
    buffer.append("[");
    if (isOpen()) buffer.append(getRemotePort());
    else buffer.append("closed");
    buffer.append("]");
    return buffer.toString();
}
