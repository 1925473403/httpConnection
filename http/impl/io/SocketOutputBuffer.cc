#include "HttpException.h"
#ifndef SOCKETOUTPUTBUFFER_H
#include "SocketOutputBuffer.h"
#endif
SocketOutputBuffer::SocketOutputBuffer(Socket *sock, int buffersize, HttpParams *params) throw (IOException) {
    if (socket == NULL) throw IllegalArgumentException("Socket may not be null");
    AbstractSessionOutputBuffer::init(socket->getOutputStream(), 8192, params);
}
