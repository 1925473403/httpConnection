#include "HttpException.h"
#ifndef SCHEME_H
#define SCHEME_H
class Scheme {
    private:
        std::string name;
        SocketFactory *socketFactory;
        int defaultPort;
        bool layered;
        std::string stringRep;
    public:
        Scheme(std::string name, SocketFactory* sockFact, int port);
        Scheme(const Scheme& rhs);
        Scheme& operator=(const Scheme& rhs);
        int getDefaultPort() { return defaultPort; }
        SocketFactory *getSocketFactory() { return socketFactory; }
        std::string getName() { return name; }
        bool isLayered() { return layered; }
        int resolvePort(int port) { return (((port <= 0) || (port > 0xffff)) ? defaultPort : port); }
        std::string toString() ;
};
#endif
