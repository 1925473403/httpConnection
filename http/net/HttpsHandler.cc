#include "URLStreamHandler.h"
#ifndef HTTPSHANDLER_H
#include "HttpsHandler.h"
#endif

HttpsHandler::HttpsHandler() : URLStreamHandler() {
    proxyport = -1;
    proxy = "";
}

int HttpsHandler::getDefaultPort() { return 443; }
HttpsHandler::HttpsHandler(std::string p, int port) : URLStreamHandler() {
    proxy = p;
    proxyport = port;
}
HttpsHandler::HttpsHandler(const HttpsHandler &rhs) {
    proxy = rhs.proxy;
    proxyport = rhs.proxyport;
}
HttpsHandler& HttpsHandler::operator=(const HttpsHandler &rhs) {
    if (this != &rhs) {
        proxy = rhs.proxy;
        proxyport = rhs.proxyport;
    }
    return *this;
}
