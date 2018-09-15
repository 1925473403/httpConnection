#include "HttpException.h"
#include "StringUtils.h"
#include "Integer.h"
#include "URLStreamHandler.h"
#include "HttpHandler.h"
#include "HttpsHandler.h"
#include "FtpHandler.h"
#include "InetSocketAddress.h"
#include "URI.h"
#include "URLStreamHandlerFactory.h"
#ifndef URL_H
#include "URL.h"
#endif

URLStreamHandlerFactory *URL::urlStreamHandlerFactory = NULL;
unordered_map<std::string, URLStreamHandler*> URL::handlers;
Parts::Parts(std::string file) {
    int ind = file.find('#');
    _ref = ((ind != std::string::npos)? file.substr(ind + 1) : "");
    file= ((ind != std::string::npos)? file.substr(0, ind): file);
    int q = file.find_last_of('?');
    if (q != std::string::npos) {
        _query = file.substr(q + 1);
        _path = file.substr(0, q);
    } else _path = file;
}
Parts::Parts(const Parts &rhs) {
    _path = rhs._path;
    _query = rhs._query;
    _ref = rhs._ref;
}
Parts& Parts::operator=(const Parts &rhs) {
    if (this != &rhs) {
        _path = rhs._path;
        _query = rhs._query;
        _ref = rhs._ref;
    }
    return *this;
}
bool URL::isValidProtocol(std::string pro) {
    int len = (int)pro.length();
    if (len == 0) return false;
    char c = pro[0];
    if (::isalpha(c) == 0) return false;
    for (int i = 1; i < len; i++) {
        c = pro[i];
        if (!isalnum(c) && c != '.' && c != '+' && c != '-') return false;
    }
    return true;
}

URL::~URL() {
    if (hostAddress) hostAddress->unref();
    if (handler) handler->unref();
}

URL::URL(const URL& rhs) {
    protocol = rhs.protocol;
    host = rhs.host;
    port = rhs.port;
    file = rhs.file;
    query = rhs.query;
    authority = rhs.authority;
    userInfo = rhs.userInfo;
    ref = rhs.ref;
    hostAddress = ((rhs.hostAddress)? new InetAddress(*rhs.hostAddress) : NULL);
    handler = URL::getURLStreamHandler(protocol);
}

URL& URL::operator=(const URL& rhs) {
    if (this != &rhs) {
        protocol = rhs.protocol;
        host = rhs.host;
        port = rhs.port;
        file = rhs.file;
        query = rhs.query;
        authority = rhs.authority;
        userInfo = rhs.userInfo;
        ref = rhs.ref;
        hostAddress = ((rhs.hostAddress)? new InetAddress(*rhs.hostAddress) : NULL);
        handler = URL::getURLStreamHandler(protocol);
    } 
    return *this;
}

URL::URL(std::string pro, std::string h, int p, std::string f) throw (MalformedURLException) : URL(pro, h, p, f, NULL) {
}

URL::URL(std::string pro, std::string h, std::string f) throw (MalformedURLException) : URL(pro, h, -1, f) {
}

URL::URL(std::string pro, std::string h, int p, std::string f, URLStreamHandler *hand) throw (MalformedURLException) : port(-1) {
    if (hand != NULL) {
    }
    toLowerCase(pro);
    protocol = pro;
    if (host != "") {
        if (h.find(':') != std::string::npos && !starts_with(h, "[")) h = "[" + h+ "]";
        host = h;
        if (p< -1) throw MalformedURLException("Invalid port number : %d", p);
        port = p;
        authority = ((port == -1)? host: (host + std::string(":") + Integer::toString(port)));
    }
    Parts parts(file);
    path = parts.getPath();
    query = parts.getQuery();
    if (query != "") file = path + "?" + query;
    else file = path;
    ref = parts.getRef();
    if (hand == NULL && (hand = URL::getURLStreamHandler(protocol)) == NULL) throw MalformedURLException("unknown protocol: %s", pro.c_str());
    handler = hand;
}

URLStreamHandler *URL::getURLStreamHandler(std::string proto) {
    URLStreamHandler *h = NULL;
    unordered_map<std::string, URLStreamHandler*>::iterator it = URL::handlers.find(proto);
    if (it != URL::handlers.end()) h = it->second;
    else {
        //bool checkedWithFactory = false;
        if (urlStreamHandlerFactory != NULL) {
            h = urlStreamHandlerFactory->createURLStreamHandler(proto);
        //    checkedWithFactory = true;
        }
        if (h == NULL) {
            std::string protolowercase = proto;
            toLowerCase(protolowercase);
            if (protolowercase == "http") { 
                h = new HttpHandler();
                URL::handlers.insert(std::make_pair("http", h));
            } else if (protolowercase == "https") {
                h = new HttpsHandler();
                URL::handlers.insert(std::make_pair("https", h));
            } else if (protolowercase == "ftp") {
                h = new FtpHandler();
                URL::handlers.insert(std::make_pair("ftp", h));
            }
        }
    }
    return h;
}

URL::URL(std::string &spec) throw (MalformedURLException) : URL(*this, spec) {
}

URL::URL(URL &context, std::string &spec) throw (MalformedURLException) : URL(context, spec, NULL) {
}

URL::URL(URL &context, std::string &spec, URLStreamHandler *h) throw (MalformedURLException) : protocol(""), host(""), path(""), port(-1),
     file(""),
     query(""),
     authority(""),
     userInfo(""),
     ref(""),
     hostAddress(0),
     handler(0) {
    std::string original;
    original.assign(spec);
    int i, limit, c;
    int start = 0;
    std::string newProtocol = "";
    bool aRef=false;
    bool isRelative = false;
    try {
        limit = (int)spec.length();
        while ((limit > 0) && (spec[limit - 1] <= ' ')) limit --;
        while ((start < limit) && (spec[start] <= ' ')) start++;
        if (spec.find("url:", start) != std::string::npos) start += 4;
        if (start < (int)spec.length() && spec[start] == '#') aRef = true;
        for (i = start ; !aRef && (i < limit) && ((c = spec[i]) != '/'); i++) {
            if (c == ':') {
                std::string s = spec.substr(start, i);
                toLowerCase(s);
                if (isValidProtocol(s)) {
                    newProtocol = s;
                    start = i +  1;
                }
                break;
            }
        }
        protocol = newProtocol;
        if ((this != &context) && ((newProtocol == "") || equalsIgnoreCase(newProtocol, context.getProtocol()))) {
            if (h == NULL) h = context.handler;
            if (context.getPath() != "" && starts_with(context.getPath(), "/")) newProtocol = "";
            if (newProtocol == "") {
                protocol = context.getProtocol();
                authority = context.getAuthority();
                userInfo = context.getUserInfo();
                host = context.getHost();
                port = context.getPort();
                file = context.getFile();
                path = context.getPath();
                isRelative = true;
            }
        }
        if (protocol == "") throw MalformedURLException("no protocol: %s", original.c_str());
        if (h == NULL && (h = getURLStreamHandler(protocol)) == NULL) throw MalformedURLException("unknown protocol: %s", protocol.c_str());
        handler = h;
        i = spec.find('#', start);
        if (i != std::string::npos && i >= 0) {
            ref = spec.substr(i + 1, limit);
            limit = i;
        }
        if (isRelative && start == limit) {
            query = context.getQuery();
            if (ref == "") ref = context.getRef();
        }
        handler->parseURL(*this, spec, start, limit);
    } catch (const MalformedURLException &e) {
        throw;
    } catch (const std::exception &e) {
        MalformedURLException ex(e.what());
        throw ex;
    }
}

void URL::set(std::string pro, std::string h, int p, std::string f, std::string r) {
    protocol = pro;
    host = h;
    authority = ((p == -1) ? host : (host + std::string(":") + Integer::toString(p)));
    port = p;
    file = f;
    ref = r;
    hostAddress = NULL;
    int q = file.find_last_of('?');
    if (q != std::string::npos) {
        query = file.substr(q+1);
        path = file.substr(0, q);
    } else path = file;
}

void URL::set(std::string pro, std::string h, int p, std::string auth, std::string ui, std::string pt, std::string q, std::string rr) {
    protocol = pro;
    host = h;
    port = p;
    authority = auth;
    userInfo = ui;
    query = q;
    ref = rr;
    path = pt;
    file = ((query == "")?path:(path + "?" + query));
    hostAddress = NULL;
}

std::string URL::getQuery() {
    return query;
}

std::string URL::getProtocol() {
    return protocol;
}

std::string URL::getPath() {
    return path;
}

std::string URL::getUserInfo() {
    return userInfo;
}

std::string URL::getAuthority() {
    return authority;
}

int URL::getPort() {
    return port;
}

int URL::getDefaultPort() {
    return handler->getDefaultPort();
}

std::string URL::getHost() {
    return host;
}

std::string URL::getFile() {
    return file;
}

std::string URL::getRef() {
    return ref;
}

bool URL::sameFile(URL &other) {
    return handler->sameFile(*this, other);
}

std::string URL::toString() {
    return toExternalForm();
}

std::string URL::toExternalForm() {
    return handler->toExternalForm(*this);
}

URI URL::toURI() throw (URISyntaxException) {
    URI uri(toString());
    return uri;
}
