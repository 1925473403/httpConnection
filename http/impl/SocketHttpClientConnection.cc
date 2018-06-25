#include "SocketHttpClientConnection.h"
SocketHttpClientConnection::SocketHttpClientConnection() { }
SocketHttpClientConnection::~SocketHttpClientConnection() { }
SessionInputBuffer* SocketHttpClientConnection::createSessionInputBuffer(Socket &, int, HttpParams*) throws IOException {
    return new SocketInputBuffer(socket, buffersize, params);
}
SessionOutputBuffer* SocketHttpClientConnection::createSessionOutputBuffer(Socket &, int, HttpParams*) throws IOException {
    return new SocketOutputBuffer(socket, buffersize, params);
}
void SocketHttpClientConnection::bind(Socket &s, HttpParams* params) throws IOException {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    socket = s;
    int buffersize = HttpConnectionParams::getSocketBufferSize(params);
    init(createSessionInputBuffer(socket, buffersize, params), createSessionOutputBuffer(socket, buffersize, params), params);
    open = true;
}
TCPAddr SocketHttpClientConnection::getLocalAddress() {
    return socket.getLocalAddress();
}
int SocketHttpClientConnection::getLocalPort() const {
    socket.getLocalPort();
}
TCPAddr SocketHttpClientConnection::getRemoteAddress() {
    socket.getInetAddress();
}
int SocketHttpClientConnection::getRemotePort() const {
    socket.getPort();
}
void SocketHttpClientConnection::setSocketTimeout(int timeout) {
    assertOpen();
}
int SocketHttpClientConnection::getSocketTimeout() const {
}
void SocketHttpClientConnection::shutdown() throws IOException {
    open = false;
    socket.close();
}
void SocketHttpClientConnection::close() throws IOException {
    if (!open) return;
    open = false;
    doFlush();
    try {
        try {
            socket.shutdownOutput();
        } catch (const IOException &e) {
        try {
            socket.shutdownInput();
        } catch (const IOException &e) {
        }
    } catch(const UnsupportedOperationException &ignore) {
    }
    socket.close();
}
