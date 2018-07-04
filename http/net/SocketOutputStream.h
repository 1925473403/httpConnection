#include "HttpException.h"
#ifndef SOCKETOUTPUTSTREAM_H
#define SOCKETOUTPUTSTREAM_H
class SocketOutputStream : public OutputStream {
     private:
        AbstractPlainSocketImpl *impl;
        char *temp;
        Socket *socket;
        bool closing;
        int socketWrite(int fd);
    public:
        SocketOutputStream(AbstractPlainSocketImpl *);
        int write(char *b, int blen, int len) throw (IOException);
        int write(char *b, int blen, int off, int len) throw (IOException);
        int write(int b) throw (IOException);
        void close() throw (IOException);
};
#endif
