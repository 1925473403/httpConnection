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
#include "AbstractPlainSocketImpl.h"
#ifndef SOCKETOUTPUTSTREAM_H
#include "SocketOutputStream.h"
#endif
#include "Socket.h"
SocketOutputStream::SocketOutputStream(AbstractPlainSocketImpl *_impl): impl(_impl), closing(false), temp(NULL), socket(NULL) {
    socket = impl->getSocket();
    temp = new char [1];
    closing = false;
}
SocketOutputStream::~SocketOutputStream() {
    delete[] temp;
}

int SocketOutputStream::socketWrite(int fd, char *b, int blen, int off, int len) {
    int n = -1;
    assert(blen - off > 0);
    n = ::write(fd, b+off, std::min<int>(blen - off, len));
    return n;
}
int SocketOutputStream::write(char *b, int blen, int len) throw (IOException) {
    return write(b, blen, 0, len);
}
int SocketOutputStream::write(char *b, int blen, int off, int len) throw (IOException) {
    int n = -1;
    if (len <= 0 || off < 0 || len > blen - off) {
        if (len == 0) return len;
        throw ArrayIndexOutOfBoundsException("len == %s off == %d buffer length == %d", len, off, blen);
    }
    int fd = impl->acquireFD();
    try {
        n = socketWrite(fd, b, blen, off, len);
        if (n > 0) {
            impl->releaseFD();
            return n;
        }
    } catch (const SocketException &e) {
        if (impl->isClosedOrPending()) {
            impl->releaseFD();
            throw SocketException("Socket closed");;
        } else {
            impl->releaseFD();
            throw;
        }
    }
    impl->releaseFD();
    return n;
}
int SocketOutputStream::write(int b) throw (IOException) {
    temp[0] = (unsigned char) b;
    return write(temp, 1, 1);
}
void SocketOutputStream::close() throw (IOException) {
    if (closing) return;
    closing = true;
    if (socket != NULL) {
        if (!socket->isClosed()) {
            socket->close();
        }
    } else impl->close();
    closing = false;
}
