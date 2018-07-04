#include "InputStream.h"
#include "AbstractPlainSocketImpl.h"
#include "Socket.h"
#ifndef SOCKETINPUTSTREAM_H
#include "SocketInputStream.h"
#endif
SocketInputStream::SocketInputStream(AbstractPlainSocketImpl *_impl) : impl(_impl) {
    socket = impl->getSocket();
}
int SocketInputStream::read(char *b, int blen, int len) throw (IOException) {
    return read(b, blen, 0, len);
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
        n = socket->read(b, blen, off, len);
        return n;
    } catch (ConnectionResetException &e) {
        gotReset = true;
    }
    impl->releaseFD();
    if (impl->isClosedOrPending()) throw SocketException("Socket closed");
    if (impl->isConnectionResetPending()) impl->setConnectionReset();
    if (impl->isConnectionReset()) throw SocketException("Connection reset");
    eof = true;
    return -1;
}
int SocketInputStream::read() throw (IOException) {
    temp = new unsigned char[1];
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
    unsigned char *data = new unsigned char [buflen];
    while (n > 0) {
        int r = read(data, buflen, std::min<int>(buflen, n));
        if (r < 0) break;
        n-=r;
    }
    delete[] data;
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
