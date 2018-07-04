#include "HttpException.h"
#ifndef FTPHANDLER_H
#define FTPHANDLER_H
class FtpHandler : public URLStreamHandler {
    protected:
        std::string proxy;
        int proxyport;
        int getDefaultPort();
    public:
        FtpHandler();
        FtpHandler(std::string p, int port);
        FtpHandler(const FtpHandler &rhs);
        FtpHandler& operator=(const FtpHandler &rhs);
};
#endif
