#include "AbstractPlainSocketImpl.h"
#include "Socket.h"
#ifndef SOCKETOUTPUTSTREAM_H
#include "SocketOutputStream.h"
#endif
SocketOutputStream::SocketOutputStream(AbstractPlainSocketImpl *_impl): impl(_impl) {
    socket = impl->getSocket();
    temp = new char [1];
    closing = false;
}
int SocketOutputStream::write(char *b, int blen, int len) throw (IOException) {
    write(b, blen, 0, len);
}
int SocketOutputStream::write(char *b, int blen, int off, int len) throw (IOException) {
    if (len <= 0 || off < 0 || len > blen - off) {
        if (len == 0) return len;
        throw ArrayIndexOutOfBoundsException("len == %s off == %d buffer length == %d", len, off, blen);
    }
    impl.acquireFD();
    try {
        socket->write(b, blen, off, len);
    } catch (const SocketException &e) {
        if (impl->isClosedOrPending()) {
            impl.releaseFD();
            throw SocketException("Socket closed");;
        } else {
            impl.releaseFD();
            throw;
        }
    }
    impl.releaseFD();
}
int SocketOutputStream::write(int b) throw (IOException) {
    temp[0] = (unsigned char) b;
    write(temp, 1, 1);
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
