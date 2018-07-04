#include "HttpException.h"
#ifndef SOCKETINPUTBUFFER_H
#include "SocketInputBuffer.h"
#endif
SocketInputBuffer::SocketInputBuffer(Socket _s, int buffersize, HttpParams *params) throw (IOException) {
    socket = _s;
    init(socket.getInputStream(), 8192, params);
}
bool SocketInputBuffer::isDataAvailable(int timeout) throw (IOException) {
    bool result = hasBufferedData();
    if (!result) {
        int oldTimeout = socket.getSoTimeout();
        try {
            socket.setSoTimeout(timeout);
            fillBuffer();
            result = hasBufferedData();
        } catch (const InterruptedIOException &e) {
            socket.setSoTimeout(oldTimeout);
            throw;
        }
        socket.setSoTimeout(oldTimeout);
    }
    return result;
}
bool SocketInputBuffer::isStale() throw (IOException) {
    if (hasBufferedData()) return false;
    int oldTimeout = socket.getSoTimeout();
    try {
        socket.setSoTimeout(1);
        return fillBuffer() == -1;
    } catch (const SocketTimeoutException &e) {
        return false;
    } catch (const IOException &e) {
        return true;
    } catch (...) {
    }
    socket.setSoTimeout(oldTimeout);
}
