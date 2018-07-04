#include "HttpException.h"
class URL;
class InetAddress;
#ifndef URLSTREAMHANDLER_H
#define URLSTREAMHANDLER_H
class URLStreamHandler {
    public:
        virtual void parseURL(URL &u, std::string spec, int start, int limit);
        virtual int getDefaultPort() { return -1; }
        virtual void setURL(URL &u, std::string protocol, std::string host, int port, std::string authority, std::string userInfo, std::string path, std::string query, std::string ref);
        virtual void setURL(URL &u, std::string protocol, std::string host, int port, std::string file, std::string ref);
        virtual InetAddress* getHostAddress(URL &u);
        virtual bool hostsEqual(URL &u1, URL &u2);
        virtual bool sameFile(URL &u1, URL &u2);
        virtual std::string toExternalForm(URL &u);
        URLStreamHandler() { }
        virtual ~URLStreamHandler() { }
};
#endif
