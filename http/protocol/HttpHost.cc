#include "HttpHost.h"
#include "CharArrayBuffer.h"
std::string HttpHost::DEFAULT_SCHEME_NAME("http");
std::string HttpHost::toLowerCase(std::string s) {
    for (int i = 0; i < s.length(); i++) s[i] = tolower(s[i]);
    return s;
}

HttpHost::HttpHost(std::string h, int p, std::string s) {
    if (h.length() == 0) throw IllegalArgumentException("Host name may not be null");
    hostname   = h;
    lcHostname = HttpHost::toLowerCase(hostname);
    if (s.length() != 0) schemeName = HttpHost::toLowerCase(s);
    else schemeName = DEFAULT_SCHEME_NAME;
    port = p;
}

HttpHost::HttpHost(const HttpHost &rhs) {
    hostname = rhs.getHostName();
    lcHostname = HttpHost::toLowerCase(hostname);
    port = rhs.getPort();
    schemeName = rhs.getSchemeName();
}

HttpHost& HttpHost::operator=(const HttpHost& rhs) {
    if (this != &rhs) {
        hostname = rhs.getHostName();
        lcHostname = HttpHost::toLowerCase(hostname);
        port = rhs.getPort();
        schemeName = rhs.getSchemeName();
    }
    return *this;
}

std::string HttpHost::toURI() {
    CharArrayBuffer buffer(32);
    buffer.append(schemeName);
    buffer.append("://");
    buffer.append(hostname);
    if (port != -1) {
        buffer.append(':');
        buffer.append(port);
    }
    return buffer.toString();
}
std::string HttpHost::toHostString() {
    CharArrayBuffer buffer(32);
    buffer.append(hostname);
    if (port != -1)  {
        buffer.append(':');
        buffer.append(port);
    }
    return buffer.toString();
}
std::string HttpHost::toString() {
    return toURI();
}
bool HttpHost::equals(const HttpHost &rhs) const {
    if (this == &rhs) return true;
    return ((lcHostname == rhs.lcHostname) && (port == rhs.getPort()) && (schemeName == rhs.getSchemeName()));
}
long HttpHost::hashCode() {
    long hash = std::hash<std::string>{} (lcHostname);
    hash ^= std::hash<int>{} (port);
    hash ^= std::hash<std::string>{} (schemeName);
    return hash;
}
