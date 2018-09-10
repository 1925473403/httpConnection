#include "HttpException.h"
#ifndef SOCKETOUTPUTSTREAM_H
#define SOCKETOUTPUTSTREAM_H
class AbstractPlainSocketImpl;
class Socket;
class SocketOutputStream : public OutputStream {
     private:
        AbstractPlainSocketImpl *impl;
        char *temp;
        Socket *socket;
        bool closing;
        int socketWrite(int fd, char *b, int blen, int off, int len);
    public:
        SocketOutputStream(AbstractPlainSocketImpl *);
        ~SocketOutputStream();
        int write(char *b, int blen, int len) throw (IOException);
        int write(char *b, int blen, int off, int len) throw (IOException);
        int write(int b) throw (IOException);
        void close() throw (IOException);
};
#endif
