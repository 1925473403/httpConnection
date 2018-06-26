#include "URI.h"
URI::URI(std::string str) throw (URISyntaxException) {
    Parser p(str)
    p.parse(false);
}
URI::URI(std::string scheme, std::string userInfo, std::string host, int port, std::string path, std::string query, std::string fragment) throw (URISyntaxException) {
    std::string s = toString(scheme, "", "", userInfo, host, port, path, query, fragment);
    checkPath(s, scheme, path);
    Parser p(s);
    p.parse(true);
}
URI::URI(std::string scheme, std::string authority, std::string path, std::string query, std::string fragment) throw (URISyntaxException) {
    std::string s = toString(scheme, "", authority, "", "", -1, path, query, fragment);
    checkPath(s, scheme, path);
    Parser p(s);
    p.parse(false);
}
URI::URI(std::string scheme, std::string host, std::string path,, std::string fragment) throw (URISyntaxException) : URI(scheme, "", host, -1, path, "", fragment) { }
URI::URI(std::string scheme, std::string ssp, std::string fragment) throw (URISyntaxException) {
    std::string s = toString(scheme, ssp, "", "", "", -1, "", "", fragment);
    Parser p(s);
    p.parse(false);
}
URI URI::create(std::string str) {
    URI u;
    try {
        u = URI(str);
    } catch (const URISyntaxException &e) {
        throw IllegalArgumentException(e.what());
    }
    return u;
}

URI& URI::parseServerAuthority() throw (URISyntaxException) {
    if (host.length() > 0 && authority.length() == 0) return *this;
    defineString();
    Parser p(string);
    p.parse(true);
    return *this;
}

URI& URI::normalize() { 
    normalize(*this);
    return *this;
}

URI& URI::resolve(URI &uri) {
    resolve(*this, uri);
    return *this;
}

URI& URI::resolve(std::string str) {
    resolve(URI::create(str));
    return *this;
}
URI& URI::relativize(URI &uri) {
    relativize(*this, uri);
    return *this;
}
URL URI::toURL() throw (MalformedURLException) {
    URL u;
    return u;
}

std::string URI::getScheme() { return scheme; }
bool URI::isAbsolute() { return (scheme.lenght() != 0); }
bool URI::isOpaque() { return path.length() == 0; }
std::string URI::getRawSchemeSpecificPart() {
    defineSchemeSpecificPart();
    return schemeSpecificPart;
}

std::string URI::getSchemeSpecificPart() {
    if (decodedSchemeSpecificPart.length() == 0) decodedSchemeSpecificPart = decode(getRawSchemeSpecificPart());
    return decodedSchemeSpecificPart;
}

std::string URI::getRawAuthority() { return authority; }
std::string URI::getAuthority() {
    if (decodedAuthority.length() == 0) decodedAuthority = decode(authority);
    return decodedAuthority;
}
std::string URI::getRawUserInfo() { return userInfo; }
std::string URI::getUserInfo() {
    if ((decodedUserInfo.length() == 0) && (userInfo.length() != 0))
        decodedUserInfo = decode(userInfo);
    return decodedUserInfo;
}
std::string URI::getHost() { return host; }
int URI::getPort() { return port; }
std::string URI::getRawPath() { return path; }
std::string URI::getPath() {
    if ((decodedPath.length() == 0) && (path.length() != 0)) decodedPath = decode(path);
    return decodedPath;
}
std::string URI::getRawQuery() { return query; }
std::string URI::getQuery() {
    if ((decodedQuery.length() == 0) && (query.length() != 0)) decodedQuery = decode(query);
    return decodedQuery;
}
std::string URI::getRawFragment() { return fragment; }
std::string URI::getFragment() {
    if ((decodedFragment.length() == 0) && (fragment.length() != 0)) decodedFragment = decode(fragment);
    return decodedFragment;
}
bool URI::equals(URI &ob) {
}
int URI::hashCode() {
    return 0;
}
int URI::compareTo(URI &that) {
}
std::string URI::toString() {
    defineString();
    return string;
}
std::string URI::toASCIIString() {
    defineString();
    return string;
}
int URI::toLower(char c) { tolower(c); }
int URI::toUpper(char c) { toupper(c); }
bool URI::equal(std::string s, std::string t) {
    if (s == t) return true;
    if (s.length() > 0 && t.length() > 0) {
        if (s.length() != t.length()) return false;
        if (s.find('%') == std::string::npos) return s == t;
        int n = s.length();
        for (int i = 0; i < n;) {
            char c = s[i];
            char d = t[i];
            if (c != '%') {
                if (c != d) return false;
                i++;
                continue;
            }
            if (d != '%') return false;
            i++;
            if (toLower(s[i]) != toLower(t[i])) return false;
            i++;
            if (toLower(s[i]) != toLower(t[i])) return false;
            i++;
        }
        return true;
    }
    return false;
}
bool URI::equalIgnoringCase(std::string s, std::string t) {
    if (s == t) return true;
    if (s.length() > 0 && t.length() > 0) {
        int n = s.length();
        if (t.length() != n) return false;
        for (int i = 0; i < n; i++) {
            if (toLower(s[i]) != toLower(t[i])) return false;
        }
        return true;
    }
    return false;
}
int URI::hash(int hash, std::string s) {
    return 0;
}
int URI::compare(std::string s, std::string t) {
    if (s == t) return 0;
    if (s.length() > 0) {
        if (t.length() > 0) return strcmp(s.c_str(), t.c_str());
        else return 1;
    } 
    return -1;
}
int URI::compareIgnoringCase(std::string s, std::string t) {
    if (s == t) return 0;
    if (s.length() > 0) {
        if (t.length() > 0) {
            int sn = s.length();
            int tn = t.length();
            int n = sn < tn ? sn : tn;
            for (int i = 0; i < n; i++) {
                int c = toLower(s[i]) - toLower(t[i]);
                if (c != 0) return c;
            }
            return sn - tn;
        }
        return 1;
    }
    return -1;
}

void URI::checkPath(std::string s, std::string scheme, std::string path) throw (URISyntaxException) {
    if (scheme.length() > 0) {
        if ((path.length() > 0) && (path[0] != '/')) throw URISyntaxException(s, "Relative path in absolute URI");
    }
}

void URI::appendAuthority(stringstream &ss, std::string authority, std::string userInfo, std::string host, int port) {
    if (host.length() > 0) {
        sb << "//";
        if (userInfo.length() > 0) {
        }
    }
}
