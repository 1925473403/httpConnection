#include "HttpException.h"
#ifndef PLAINSOCKETFACTORY_H
#define PLAINSOCKETFACTORY_H
class PlainSocketFactory : public SocketFactory {
        virtual ~PlainSocketFactory() { }
    public:
        static PlainSocketFactory DEFAULT_FACTORY;
        static PlainSocketFactory getSocketFactory();
        PlainSocketFactory();
        void unref();
        Socket *createSocket();
        Socket *connectSocket(Socket *sock, std::string host, int port, InetAddress *localAddress, int localPort, HttpParams *params) throw (IOException);
        bool isSecure(Socket *sock);
};
#endif
