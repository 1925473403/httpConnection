#include "HttpException.h"
#ifndef HTTPHOST_H
#define HTTPHOST_H
class HttpHost {
    static std::string DEFAULT_SCHEME_NAME;
    protected:
        std::string hostname;
        std::string lcHostname;
        int port;
        std::string schemeName;
    public:
        static std::string toLowerCase(std::string s);
        HttpHost(std::string h, int p = -1, std::string s= "");
        HttpHost(const HttpHost&);
        HttpHost& operator=(const HttpHost &);
        std::string getHostName() const { return hostname; }
        int getPort() const { return port; }
        std::string getSchemeName() const { return schemeName; }
        std::string toURI();
        std::string toHostString();
        std::string toString();
        bool equals(const HttpHost &rhs) const;
        long hashCode();
};
#endif
