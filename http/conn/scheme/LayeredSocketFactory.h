#include "HttpException.h"
#include "SocketFactory.h"
#ifndef LAYEREDSOCKETFACTORY_H
#define LAYEREDSOCKETFACTORY_H
class LayeredSocketFactory : public SocketFactory {
    public:
        virtual ~LayeredSocketFactory() { }
        virtual Socket* createSocket(Socket *sock, std::string host, int port, bool autoClose) throw (IOException, UnknownHostException) = 0;
};
#endif
