#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <pthread.h>
#include "HttpException.h"
#include "InetSocketAddress.h"
#include "SocketImpl.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "NameResolver.h"
#include "SocketImpl.h"
#include "AbstractPlainSocketImpl.h"
#ifndef SOCKETINPUTSTREAM_H
#include "SocketInputStream.h"
#endif
#include "Socket.h"
SocketInputStream::SocketInputStream(AbstractPlainSocketImpl *_impl) : eof(false), impl(_impl), temp(NULL), closing(false) {
    socket = impl->getSocket();
}
int SocketInputStream::read(char *b, int blen, int len) throw (IOException) {
    return read(b, blen, 0, len);
}

void SocketInputStream::setEOF(bool e) {
    eof = e;
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
        if (n > 0) {
            impl->releaseFD();
            return n;
        }
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
    /*
     * int timeout = impl->getOption(SO_RCVTIMEO);
     * if (timeout <= 0) {
     *     n = ::read(fd, b + off, std::min<int>(blen - off, len));
     * } else {
     *     struct pollfd pfds[2] = { 0 };
     *     pfds[0].events = 0;
     *     pfds[0].events |= POLLIN | POLLPRI;
     *     pfds[0].fd = fd;
     *     int rc = poll(pfds, 1, timeout);
     *     for (int count  = 0; rc > 0 && count >= 0; count --) {
     *         struct pollfd *p = pfds + count;
     *         if (p->revents) {
     *             if (p->revents & (POLLIN | POLLPRI)) {
     *                 n = ::read(fd, b + off, std::min<int>(blen - off, len));
     *             }
     *         }
     *     }
     * }
     * return n;
     */
    n = ::read(fd, b + off, std::min<int>(blen - off, len));
    return n;
}
int SocketInputStream::read() throw (IOException) {
    char tchar;
    int n = read(&tchar, 1, 1);
    if (n < 0) {
        return -1;
    }
    unsigned char t = tchar & 0xff;
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
