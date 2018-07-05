#include "HttpException.h"
#ifndef SOCKETOUTPUTBUFFER_H
#define SOCKETOUTPUTBUFFER_H
class SocketOutputBuffer : public AbstractSessionOutputBuffer {
    public:
        SocketOutputBuffer(Socket *sock, int buffersize, HttpParams *params) throw (IOException);
};
#endif
