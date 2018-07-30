#include "HttpException.h"
#ifndef DUALSTACKPLAINSOCKETIMPL_H
#define DUALSTACKPLAINSOCKETIMPL_H
class DualStackPlainSocketImpl : public AbstractPlainSocketImpl {
    private:
        bool exclusiveBind;
        bool isReuseAddress;
        int checkAndReturnNativeFD() throw (SocketException);
    public:
        DualStackPlainSocketImpl(bool exclBind);
        DualStackPlainSocketImpl(int fd, bool exclBind);
        void socketCreate(bool stream) throw(IOException);
        void socketConnect(InetAddress *address, int port, int timeout) throw (IOException);
        void socketBind(InetAddress *address, int port) throw(IOException);
        void socketListen(int backlog) throw(IOException);
        void socketAccept(SocketImpl *s) throw(IOException);
        void socketClose0(bool useDeferredClose) throw(IOException);
        void socketShutdown(int howto) throw(IOException); 
        void socketSendUrgentData(int data) throw(IOException);
        int socketAvailable() throw (IOException);
};
#endif
