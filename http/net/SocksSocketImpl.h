#include "HttpException.h"
#ifndef SOCKSSOCKETIMPL_H
#define SOCKSSOCKETIMPL_H
class SocksSocketImpl : public PlainSocketImpl, public SocksConsts {
    private:
        std::string server;
        int serverPort;
        InetSocketAddress *external_address;
        bool useV4;
        Socket *cmdsock;
        InputStream *cmdIn;
        OutputStream *cmdOut;
        bool applicationSetProxy;
    public:
        SocksSocketImpl();
        SocksSocketImpl(std::string &s, int port);
        void setV4() ;
        void privilegedConnect(std::string &host, int port, int timeout) throw (IOException);
        void superConnectServer(std::string &host, int port, int timeout) throw (IOException);
        static int remainingMillis(long deadlineMillis) throw (IOException);
        int readSocksReply(InputStream *in, unsigned char *data, int len) throw (IOException);
        int readSocksReply(InputStream *in, unsigned char *data, long deadlineMillis) throw (IOException);
        bool authenticate(unsigned char method, InputStream *in, 
};
#endif
