#include "URLStreamHandler.h"
#ifndef FTPHANDLER_H
#include "FtpHandler.h"
#endif

FtpHandler::FtpHandler() : URLStreamHandler() {
    proxyport = -1;
    proxy = "";
}

int FtpHandler::getDefaultPort() { return 21; }
FtpHandler::FtpHandler(std::string p, int port) : URLStreamHandler() {
    proxy = p;
    proxyport = port;
}
FtpHandler::FtpHandler(const FtpHandler &rhs) {
    proxy = rhs.proxy;
    proxyport = rhs.proxyport;
}
FtpHandler& FtpHandler::operator=(const FtpHandler &rhs) {
    if (this != &rhs) {
        proxy = rhs.proxy;
        proxyport = rhs.proxyport;
    }
    return *this;
}
