#include "Integer.h"
#include "Stokenizer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#ifndef INETSOCKETADDRESS_H
#include "InetSocketAddress.h"
#endif
#include "NameResolver.h"
#include <regex>

ostream& operator<<(ostream &os, InetAddress &rhs) {
    os << "Hostname: " << rhs.gethostname() << ", ip address: " << rhs.getipaddr() << std::endl;
    return os;
}

InetAddress::InetAddress() { }
InetAddress::InetAddress(std::string &src) : InetAddress(src.c_str()) { }
InetAddress::InetAddress(const char *str) {
    vector<std::string> res;
    assert(str != NULL);
    std::string sstr(str);
    if (std::regex_match(sstr, std::regex("([0-9]+).([0-9]+).([0-9]+).([0-9]+)"))) {
        ipaddr.assign(str);
        NameResolver::getnameinfo(str, res);
        if (res.size()) hostname = res[0];
    } else {
        hostname.assign(str);
        NameResolver::resolve(str, res);
        assert(res.size() > 0);
        ipaddr = res[0];
    }
}

InetAddress* InetAddress::anyLocalAddress() {
    return new InetAddress("0.0.0.0");
}

InetAddress* InetAddress::getLocalHost() {
    char name[1024];
    memset(name, 0, 1024);
    if (::gethostname(name, 1023) != 0) {
        strcpy(name, "localhost");
    }
    InetAddress *r = new InetAddress(name);
    return r;
}

InetAddress* InetAddress::getByName(std::string &host) throw (UnknownHostException) {
    return getByName(host.c_str());
}
InetAddress* InetAddress::getByName(const char *host) throw (UnknownHostException) {
    vector<InetAddress *> res;
    InetAddress::getAllByName(host, res);
    InetAddress *r = res[0];
    for (size_t i = 1; i < res.size(); i++) 
        res[i]->unref();
    res.clear();
    return r;
}

void InetAddress::getAllByName(const char *host, vector<InetAddress *> &res) throw (UnknownHostException) {
    InetAddress::getAllByName(host, res, NULL);
}

std::string InetAddress::toString() {
    std::stringstream ss;
    std::string h = gethostname();
    if (h.length() != 0) return h;
    h = "/" + getipaddr();
    return h;
}
void InetAddress::getAllByName(const char* host, vector<InetAddress *> &res, InetAddress* reqAddr) throw (UnknownHostException) {
    if (host == NULL) {
        res.push_back(new InetAddress("127.0.0.1"));
        return;
    }
    vector<std::string> ips;
    NameResolver::resolve(host, ips);
    assert(ips.size() > 0);
    size_t i = 0;
    for (i = 0; reqAddr && i < ips.size(); i++) {
        if (reqAddr->getipaddr() == ips[i]) break;
    }
    if (reqAddr && (i < ips.size()|| i == ips.size())) {
        res.push_back(reqAddr);
    } else res.push_back(new InetAddress(ips[0]));
}

int InetAddress::compareTo(InetAddress &rhs) {
    if (this == &rhs) return 0;
    if (hostname == rhs.hostname) {
        if (ipaddr == rhs.ipaddr) return 0;
        else if (ipaddr > rhs.ipaddr) return 1;
        else return -1;
    }
    if (hostname > rhs.hostname) return 1;
    else return -1;
}
InetAddress::InetAddress(const InetAddress &rhs) {
    hostname = rhs.hostname;
    ipaddr = rhs.ipaddr;
}
InetAddress& InetAddress::operator=(const InetAddress &rhs) {
    if (this != &rhs) {
        hostname = rhs.hostname;
        ipaddr = rhs.ipaddr;
    }
    return *this;
}
InetSocketAddress::InetSocketAddress(std::string &host, int p) : InetSocketAddress(host.c_str(), port) {
}
InetSocketAddress::InetSocketAddress(InetAddress *addr, int p) {
    hostname="";
    bzero(&si_addr, sizeof(si_addr));
    si_addr.sin_family = AF_INET;
    si_addr.sin_port = p;//htons(p);
    printf("%x:%x:%x:%x\n", p, htons(p), si_addr.sin_port, htons(htons(p)));
    port = p;
    if (addr == NULL) {
        si_addr.sin_addr.s_addr = INADDR_ANY;
        hostname.assign("0.0.0.0");
        this->addr = new InetAddress("0.0.0.0");
    } else if (addr->gethostname() == "") {
        hostname.assign(addr->getipaddr().c_str());
        si_addr.sin_addr.s_addr = inet_addr(addr->getipaddr().c_str());
        this->addr = addr;
        this->addr->ref();
    } else {
        vector<std::string> res;
        NameResolver::resolve(addr->gethostname().c_str(), res);
        addr->setipaddr(res[0]);
        hostname.assign(res[0].c_str());
        si_addr.sin_addr.s_addr = inet_addr(res[0].c_str());
        this->addr = addr;
        this->addr->ref();
    }
}

bool InetSocketAddress::isUnresolved() {
    struct sockaddr_in tmp;
    bzero(&tmp, sizeof(tmp));
    return memcmp((void *)&tmp, (void *)&si_addr, sizeof(tmp)) == 0;
}

struct sockaddr_in& InetSocketAddress::getSockAddress() {
    return si_addr;
}

InetAddress* InetSocketAddress::getAddress() {
    if (addr) addr->ref();
    return addr;
}

int InetSocketAddress::getPort() {
    return port;
}

std::string InetSocketAddress::getHostName() {
    return hostname;
}

std::string InetSocketAddress::toString() {
    std::stringstream ss;
    ss << hostname << ":" << port;
    return ss.str();
}

InetSocketAddress::~InetSocketAddress() {
    if (addr) addr->unref();
}

InetSocketAddress::InetSocketAddress(const char *host, int p) : hostname(host), port(p) {
    vector<std::string> res;
    const char *ipaddr = NULL;
    if (host != NULL) {
        std::string sstr(host);
        if (std::regex_match(sstr, std::regex("([0-9]+).([0-9]+).([0-9]+).([0-9]+)"))) {
            NameResolver::getnameinfo(host, res);
            if (res.size()) hostname = res[0];
            ipaddr = host;
        } else {
            hostname.assign(host);
            NameResolver::resolve(host, res);
            ipaddr = res[0].c_str();
        }
        assert(ipaddr != NULL);
        bzero(&si_addr, sizeof(si_addr));
        si_addr.sin_family = AF_INET;
        si_addr.sin_addr.s_addr = inet_addr(ipaddr);
        si_addr.sin_port = port;
        addr = new InetAddress(ipaddr);
    } else {
        hostname.assign("localhost");
        bzero(&si_addr, sizeof(si_addr));
        si_addr.sin_family = AF_INET;
        si_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
        si_addr.sin_port = port;
        addr = new InetAddress("0.0.0.0");
    }
}
InetSocketAddress::InetSocketAddress() { }
InetSocketAddress::InetSocketAddress(const InetSocketAddress &rhs) {
    si_addr = rhs.si_addr;
    hostname = rhs.hostname;
    port = rhs.port;
}
InetSocketAddress& InetSocketAddress::operator=(const InetSocketAddress& rhs) {
    if (this != &rhs) {
        si_addr = rhs.si_addr;
        hostname = rhs.hostname;
        port = rhs.port;
    }
    return *this;
}
