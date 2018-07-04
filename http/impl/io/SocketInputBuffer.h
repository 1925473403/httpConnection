#include "HttpException.h"
#ifndef SOCKETINPUTBUFFER_H
#define SOCKETINPUTBUFFER_H
class SocketInputBuffer : public AbstractSessionInputBuffer {
    private:
    Socket *socket;
    public:
        SocketInputBuffer(Socket _s, int buffersize, HttpParams *params) throw (IOException);
        bool isDataAvailable(int timeout) throw (IOException);
        bool isStale() throw (IOException);
};
#endif
