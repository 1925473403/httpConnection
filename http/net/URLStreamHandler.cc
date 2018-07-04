#include "HttpException.h"
#include "CharArrayBuffer.h"
#include "InetSocketAddress.h"
#include "Integer.h"
#include "StringUtils.h"
#include "URI.h"
#include "URL.h"
#ifndef URLSTREAMHANDLER_H
#include "URLStreamHandler.h"
#endif
void URLStreamHandler::parseURL(URL &u, std::string spec, int start, int limit) {
    std::string protocol = u.getProtocol();
    std::string authority = u.getAuthority();
    std::string userInfo = u.getUserInfo();
    std::string host = u.getHost();
    int port = u.getPort();
    std::string path = u.getPath();
    std::string query = u.getQuery();

    // This field has already been parsed
    std::string ref = u.getRef();
    bool isRelPath = false;
    bool queryOnly = false;
    if (start < limit) {
        int queryStart = spec.find("?");
        queryOnly = (queryStart == start);
        if ((queryStart != std::string::npos) && (queryStart < limit)) {
            query = spec.substr(queryStart+1, limit);
            if (limit > queryStart) limit = queryStart;
            spec = spec.substr(0, queryStart);
        }
    }
    int i = 0;
    bool isUNCName = (start <= limit - 4) &&
                        (spec[start] == '/') &&
                        (spec[start+1] == '/') &&
                        (spec[start+2] == '/') &&
                        (spec[start+3] == '/');
    if (!isUNCName && (start <= limit - 2) && (spec[start] == '/') && (spec[start + 1] == '/')) {
        start += 2;
        i = spec.find('/', start);
        if (i < 0 || i > limit) {
            i = spec.find('?', start);
            if (i < 0 || i > limit) i = limit;
        }
        host = authority = spec.substr(start, i);
        int ind = authority.find('@');
        if (ind != std::string::npos) {
            if (ind != authority.find_last_of('@')) {
                userInfo = "";
                host = "";
            } else {
                userInfo = authority.substr(0, ind);
                host = authority.substr(ind+1);
            }
        } else userInfo = "";
        if (host != "") {
            if (host.length()>0 && (host[0] == '[')) {
                if ((ind = host.find(']')) != std::string::npos && (ind > 2)) {
                    std::string nhost = host ;
                    host = nhost.substr(0, ind + 1);
                    port = -1;
                    if (nhost.length() > ind+1) {
                        if (nhost[ind+1] == ':') {
                            ++ind;
                            if (nhost.length() > (ind + 1)) port = Integer::parseInt(nhost.substr(ind+1).c_str());
                        } else  throw IllegalArgumentException("Invalid authority field: %s", authority.c_str());
                    }
                } else throw IllegalArgumentException("Invalid authority field: %s", authority.c_str());
            } else {
                ind = host.find(':');
                port = -1;
                if (ind != std::string::npos && ind >= 0) {
                    if (host.length() > (ind + 1)) port = Integer::parseInt(host.substr(ind + 1));
                    host = host.substr(0, ind);
                }
            }
        } else host = "";
        if (port < -1) throw IllegalArgumentException("Invalid port number :%d", port);
        start = i;
    }
    if (host == "") host = "";
    if (start < limit) {
        if (spec[start] == '/') path = spec.substr(start, limit);
        else if (path != "" && path.length() > 0) {
            isRelPath = true;
            int ind = path.find_last_of('/');
            std::string seperator = "";
            if (ind == std::string::npos && authority != "") {
                ind = -1;
                seperator = "/";
            }
            path = path.substr(0, ind + 1) + seperator + spec.substr(start, limit);
        } else {
        }
    } else if (queryOnly && path.length() > 0) {
        int ind = path.find_last_of('/');
        if (ind == std::string::npos) ind = 0;
        path = path.substr(0, ind) + "/";
    }
    if (path.length() == 0) path = "";
    if (isRelPath) {
        while ((i = path.find("/./")) != std::string::npos) path = (path.substr(0, i) + path.substr(i+2));
        while ((i = path.find("/../", i)) != std::string::npos) {
            if (i > 0 && (limit = path.find_last_of('/', i - 1)) != std::string::npos && (path.find("/../", limit) != std::string::npos)) {
                path = path.substr(0, limit) + path.substr(i + 3);
                i = 0;
            } else i = i + 3;
        }
        while (ends_with(path, "/..")) {
            i = path.find("/..");
            if ((limit = path.find_last_of('/', i - 1)) != std::string::npos) path = path.substr(0, limit + 1);
            else break;
        }
        if (starts_with(path, "./") && path.length() > 2) path = path.substr(2);
        if (ends_with(path, "/.")) path = path.substr(0, path.length() - 2);
    }
    setURL(u, protocol, host, port, authority, userInfo, path, query, ref);
}

std::string URLStreamHandler::toExternalForm(URL &u) {
    int len = u.getProtocol().length() + 1;
    if (u.getAuthority() != "" && u.getAuthority().length() > 0) len += 2 + u.getAuthority().length();
    if (u.getPath() != "") len += u.getPath().length();
    if (u.getQuery() != "") len += 1 + u.getQuery().length();
    if (u.getRef() != "") len += 1 + u.getRef().length();
    CharArrayBuffer result(len + 1);
    result.append(u.getProtocol().c_str());
    result.append(":");
    if (u.getAuthority() != ""  && u.getAuthority().length() > 0) {
        result.append("//");
        result.append(u.getAuthority().c_str());
    }
    if (u.getPath() != "") result.append(u.getPath().c_str());
    if (u.getQuery() != "") {
        result.append('?');
        result.append(u.getQuery().c_str());
    }
    if (u.getRef() != "") {
         result.append("#");
         result.append(u.getRef().c_str());
    }
    return result.toString();
}

void URLStreamHandler::setURL(URL &u, std::string protocol, std::string host, int port, std::string authority, std::string userInfo, std::string path, std::string query, std::string ref) {
    if (this != u.handler) throw SecurityException("handler for url different from this handler");
    u.set(u.getProtocol(), host, port, authority, userInfo, path, query, ref);
}

void URLStreamHandler::setURL(URL &u, std::string protocol, std::string host, int port, std::string file, std::string ref) {
    std::string authority = "", userInfo = "";
    if (host != "" && host.length() != 0) {
        authority = ((port == -1) ? host : (host + std::string(":") + Integer::toString(port)));
        int at = host.find_last_of('@');
        if (at != std::string::npos) {
            userInfo = host.substr(0, at);
            host = host.substr(at+1);
        }
    }
    std::string path = "", query = "";
    if (file != "") {
        int q = file.find_last_of('?');
        if (q != std::string::npos) {
            query = file.substr(q + 1);
            path = file.substr(0, q);
        } else path = file;
    }
    setURL(u, protocol, host, port, authority, userInfo, path, query, ref);
}

InetAddress* URLStreamHandler::getHostAddress(URL &u) {
    if (u.hostAddress != NULL) return u.hostAddress;
    std::string host = u.getHost();
    if (host == "") return NULL;
    else {
        try {
            u.hostAddress = InetAddress::getByName(host);
        } catch (const UnknownHostException &ex) {
            return NULL;
        } catch (const SecurityException &ex) {
            return NULL;
        }
    }
    return u.hostAddress;
}

bool URLStreamHandler::hostsEqual(URL &u1, URL &u2) {
    InetAddress *a1 = getHostAddress(u1);
    InetAddress *a2 = getHostAddress(u2);
    if (a1 != NULL && a2 != NULL) return (a1->compareTo(*a2) == 0);
    else if (u1.getHost() != "" && u2.getHost() != "") return equalsIgnoreCase(u1.getHost(), u2.getHost());
    else u1.getHost() == "" && u2.getHost() == "";
}

bool URLStreamHandler::sameFile(URL &u1, URL &u2) {
    if (!((u1.getProtocol() == u2.getProtocol()) || (u1.getProtocol() != "" && equalsIgnoreCase(u1.getProtocol(), u2.getProtocol())))) return false;
    if (!(u1.getFile() == u2.getFile() || (u1.getFile() != "" && u1.getFile() != u2.getFile()))) return false;
    int port1, port2;
    port1 = (u1.getPort() != -1) ? u1.getPort() : u1.handler->getDefaultPort();
    port2 = (u2.getPort() != -1) ? u2.getPort() : u2.handler->getDefaultPort();
    if (port1 != port2) return false;
    if (!hostsEqual(u1, u2)) return false;
    return true;
}
