#include "HttpException.h"
#include "RefCount.h"
#include "Comparable.h"
#ifndef INETSOCKETADDRESS_H
#define INETSOCKETADDRESS_H

class InetAddress : public RefCount {
    std::string ipaddr;
    std::string hostname;
    public:
    InetAddress(std::string host);
    InetAddress(const char *str);
    InetAddress();
    InetAddress(const InetAddress &rhs);
    InetAddress& operator=(const InetAddress &rhs);
    int compareTo(InetAddress &rhs);
    void sethostname(std::string h) { hostname = h; }
    void setipaddr(std::string i) { ipaddr = i; }
    std::string gethostname() { return hostname; }
    std::string getipaddr() { return ipaddr; }
    std::string toString() ;
    static InetAddress* getLocalHost();
    static InetAddress* getByName(std::string name) throw (UnknownHostException);
    static InetAddress* anyLocalAddress();
    static void getAllByName(std::string name, vector<InetAddress *> &res) throw (UnknownHostException);
    static void getAllByName(std::string name, vector<InetAddress *> &res, InetAddress* reqAddr) throw (UnknownHostException);
    bool isAnyLocalAddress() { return false; }
    bool isLoopbackAddress() { return false; }
    bool isMulticastAddress() { return false; }
    bool isLinkLocalAddress() { return false; }
    bool isSiteLocalAddress() { return false; }
    bool isMCGlobal() { return false; }
    bool isMCNodeLocal() { return false; }
    bool isMCLinkLocal() { return false; }
    bool isMCSiteLocal() { return false; }
    bool isMCOrgLocal() { return false; }
};
class SocketAddress:public RefCount {
    public:
    virtual ~SocketAddress() { }
    virtual bool isUnresolved() = 0;
    virtual int getPort() =0;
    virtual std::string getHostName() = 0;
    virtual InetAddress* getAddress() = 0;
    virtual std::string toString() = 0;
};

class InetSocketAddress : public SocketAddress {
        struct sockaddr_in si_addr;
        std::string hostname;
        int port;
        bool isResolved(const char *str);
    public:
        InetSocketAddress(std::string host, int port);
        InetSocketAddress(const char *str, int port);
        InetSocketAddress(InetAddress *addr, int port);
        InetSocketAddress();
        InetSocketAddress(const InetSocketAddress &rhs);
        InetSocketAddress& operator=(const InetSocketAddress& rhs);
        InetAddress* getAddress();
        int getPort();
        string getHostName();
        bool isUnresolved();
        std::string toString();
        struct sockaddr_in& getSockAddress();
};
ostream& operator<<(ostream &os, InetAddress &rhs) ;
#endif
