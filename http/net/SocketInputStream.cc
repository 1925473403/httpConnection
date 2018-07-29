#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include "HttpException.h"
#include "SocketImpl.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "NameResolver.h"
#include "InetSocketAddress.h"
#include "SocketImpl.h"
#include "AbstractPlainSocketImpl.h"
#ifndef SOCKETINPUTSTREAM_H
#include "SocketInputStream.h"
#endif
#include "Socket.h"
SocketInputStream::SocketInputStream(AbstractPlainSocketImpl *_impl) : impl(_impl) {
    socket = impl->getSocket();
}
int SocketInputStream::read(char *b, int blen, int len) throw (IOException) {
    return read(b, blen, 0, len);
}

void SocketInputStream::init() {
}
int SocketInputStream::read(char *b, int blen, int off, int len) throw (IOException) {
    if (eof) return -1;
    if (impl->isConnectionReset()) throw SocketException("Connection reset");
    if (len <= 0 || off < 0 || len > blen - off) {
        if (len == 0) return len;
        throw ArrayIndexOutOfBoundsException("length == %d off == %d buffer length == %d", len, off, blen);
    }
    int fd = impl->acquireFD();
    try {
        int n = socketRead(fd, b, blen, off, len);
        if (n > 0) return n;
    } catch (ConnectionResetException &e) {
        //gotReset = true;
    }
    impl->releaseFD();
    if (impl->isClosedOrPending()) throw SocketException("Socket closed");
    if (impl->isConnectionResetPending()) impl->setConnectionReset();
    if (impl->isConnectionReset()) throw SocketException("Connection reset");
    eof = true;
    return -1;
}

int SocketInputStream::socketRead(int fd, char *b, int blen, int off, int len) {
    int n = -1;
    n = ::read(fd, b + off, std::min<int>(blen - off, len));
    return n;
}
int SocketInputStream::read() throw (IOException) {
    temp = new char[1];
    int n = read(temp, 1, 1);
    if (n < 0) {
        delete[] temp;
        return -1;
    }
    unsigned char t = temp[0] & 0xff;
    delete[] temp;
    return t;
}
long SocketInputStream::skip(long numbytes) throw (IOException) {
    if (numbytes <= 0) return 0;
    long n = numbytes;
    int buflen = std::min<int>(1024, n);
    char data[buflen];
    while (n > 0) {
        int r = read((char *)data, buflen, std::min<int>(buflen, n));
        if (r < 0) break;
        n -=r;
    }
    return numbytes - n;
}
int SocketInputStream::available() throw (IOException) {
    return impl->available();
}
void SocketInputStream::close() throw (IOException) {
    if (closing) return;
    closing = true;
    if (socket != NULL) {
        if (!socket->isClosed()) socket->close();
    } else impl->close();
    closing = false;
}
