#include <iostream>
#include "InetSocketAddress.h"
#include "URLStreamHandler.h"
#ifndef HTTPHANDLER_H
#include "HttpHandler.h"
#endif

HttpHandler::HttpHandler() {
    proxyport = -1;
    proxy = "";
}

int HttpHandler::getDefaultPort() { return 80; }
HttpHandler::HttpHandler(std::string p, int port) : URLStreamHandler() {
    proxy = p;
    proxyport = port;
}
HttpHandler::HttpHandler(const HttpHandler &rhs) {
    proxy = rhs.proxy;
    proxyport = rhs.proxyport;
}
HttpHandler& HttpHandler::operator=(const HttpHandler &rhs) {
    if (this != &rhs) {
        proxy = rhs.proxy;
        proxyport = rhs.proxyport;
    }
    return *this;
}
