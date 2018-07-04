#include "HttpException.h"
#include "SocketFactory.h"
#include "Integer.h"
#ifndef SCHEME_H
#include "Scheme.h"
#endif
Scheme::Scheme(std::string n, SocketFactory* sockFact, int port) : name(n), socketFactory(sockFact), defaultPort(port), layered(false) {
    if (name == "") throw IllegalArgumentException ("Scheme name may not be null");
    if (sockFact == NULL) throw IllegalArgumentException ("Socket factory may not be null");
    if ((port <= 0) || (port > 0xffff)) throw IllegalArgumentException ("Port is invalid: %d", port);
    if (dynamic_cast<LayeredSocketFactory *>(socketFactory)) layered = true;
    stringRep = "";
}
Scheme::Scheme(const Scheme& rhs) {
    name = rhs.name;
    socketFactory = rhs.socketFactory;
    defaultPort = rhs.defaultPort;
    layered = rhs.layered;
    stringRep = rhs.stringRep;
}
Scheme& Scheme::operator=(const Scheme& rhs) {
    if (this != &rhs) {
        name = rhs.name;
        socketFactory = rhs.socketFactory;
        defaultPort = rhs.defaultPort;
        layered = rhs.layered;
        stringRep = rhs.stringRep;
    }
    return *this;
}
std::string Scheme::toString() {
    if (stringRep.length() == 0) {
        stringstream ss;
        ss << name ;
        ss << ":";
        ss << Integer::toString(defaultPort);
        stringRep = ss.str();
    }
    return stringRep;
}
