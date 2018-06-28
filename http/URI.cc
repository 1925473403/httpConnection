#include "HttpException.h"
#include "URI.h"
#include "Integer.h"

long URI::L_DIGIT = URI::lowMask('0', '9');
long URI::H_DIGIT = 0L;
long URI::L_UPALPHA = 0L;
long URI::H_UPALPHA = URI::highMask('A', 'Z');
long URI::L_LOWALPHA = 0L;
long URI::H_LOWALPHA = URI::highMask('a', 'z');
long URI::L_ALPHA = L_LOWALPHA | L_UPALPHA;
long URI::H_ALPHA = H_LOWALPHA | H_UPALPHA;
long URI::L_ALPHANUM = L_DIGIT | L_ALPHA;
long URI::H_ALPHANUM = H_DIGIT | H_ALPHA;
long URI::L_HEX = L_DIGIT;
long URI::H_HEX = URI::highMask('A', 'F') | URI::highMask('a', 'f');
long URI::L_MARK = URI::lowMask("-_.!~*'()");
long URI::H_MARK = URI::highMask("-_.!~*'()");
long URI::L_UNRESERVED = L_ALPHANUM | L_MARK;
long URI::H_UNRESERVED = H_ALPHANUM | H_MARK;
long URI::L_RESERVED = URI::lowMask(";/?:@&=+$,[]");
long URI::H_RESERVED = URI::highMask(";/?:@&=+$,[]");
long URI::L_ESCAPED = 1L;
long URI::H_ESCAPED = 0L;
long URI::L_URIC = L_RESERVED | L_UNRESERVED | L_ESCAPED;
long URI::H_URIC = H_RESERVED | H_UNRESERVED | H_ESCAPED;
long URI::L_PCHAR = L_UNRESERVED | L_ESCAPED | URI::lowMask(":@&=+$,");
long URI::H_PCHAR = H_UNRESERVED | H_ESCAPED | URI::highMask(":@&=+$,");
long URI::L_PATH = L_PCHAR | URI::lowMask(";/");
long URI::H_PATH = H_PCHAR | URI::highMask(";/");
long URI::L_DASH = URI::lowMask("-");
long URI::H_DASH = URI::highMask("-");
long URI::L_DOT = URI::lowMask(".");
long URI::H_DOT = URI::highMask(".");
long URI::L_USERINFO = L_UNRESERVED | L_ESCAPED | URI::lowMask(";:&=+$,");
long URI::H_USERINFO = H_UNRESERVED | H_ESCAPED | URI::highMask(";:&=+$,");
long URI::L_REG_NAME = L_UNRESERVED | L_ESCAPED | URI::lowMask("$,;:@&=+");
long URI::H_REG_NAME = H_UNRESERVED | H_ESCAPED | URI::highMask("$,;:@&=+"); 
long URI::L_SERVER = L_USERINFO | L_ALPHANUM | L_DASH | URI::lowMask(".:@[]");
long URI::H_SERVER = H_USERINFO | H_ALPHANUM | H_DASH | URI::highMask(".:@[]");
long URI::L_SERVER_PERCENT = L_SERVER | URI::lowMask("%");
long URI::H_SERVER_PERCENT = H_SERVER | URI::highMask("%");
long URI::L_LEFT_BRACKET = URI::lowMask("[");
long URI::H_LEFT_BRACKET = URI::highMask("[");
long URI::L_SCHEME = L_ALPHA | L_DIGIT | URI::lowMask("+-.");
long URI::H_SCHEME = H_ALPHA | H_DIGIT | URI::highMask("+-.");
long URI::L_URIC_NO_SLASH = L_UNRESERVED | L_ESCAPED | URI::lowMask(";?:@&=+$,");
long URI::H_URIC_NO_SLASH = H_UNRESERVED | H_ESCAPED | URI::highMask(";?:@&=+$,");

char hexDigits[16] = { "012345678ABCDEF" };
typedef unsigned char byte;

URI::URI(std::string str) throw (URISyntaxException) : port(-1) {
    Parser p(this, str);
    p.parse(false);
}
URI::URI(std::string scheme, std::string userInfo, std::string host, int port, std::string path, std::string query, std::string fragment) throw (URISyntaxException) {
    std::string s = toString(scheme, "", "", userInfo, host, port, path, query, fragment);
    URI::checkPath(s, scheme, path);
    Parser p(this, s);
    p.parse(true);
}
URI::URI(std::string scheme, std::string auth, std::string path, std::string query, std::string fragment) throw (URISyntaxException) : port(-1) {
    std::string s = toString(scheme, "", auth, "", "", -1, path, query, fragment);
    URI::checkPath(s, scheme, path);
    Parser p(this, s);
    p.parse(false);
}
URI::URI(std::string scheme, std::string host, std::string path, std::string fragment) throw (URISyntaxException) : URI(scheme, "", host, -1, path, "", fragment) { }
URI::URI(std::string scheme, std::string ssp, std::string fragment) throw (URISyntaxException) : port(-1) {
    std::string s = toString(scheme, ssp, "", "", "", -1, "", "", fragment);
    Parser p(this, s);
    p.parse(false);
}

URI::URI(const URI &rhs) {
    scheme = rhs.scheme;
    fragment = rhs.fragment;
    authority = rhs.authority;
    userInfo = rhs.userInfo;
    host = rhs.host;
    port = rhs.port;
    path = rhs.path;
    query = rhs.query;
    schemeSpecificPart = rhs.schemeSpecificPart;
    _hash = rhs._hash;
    decodedUserInfo = rhs.decodedUserInfo;
    decodedAuthority= rhs.decodedAuthority;
    decodedPath = rhs.decodedPath;
    decodedQuery = rhs.decodedQuery;
    decodedFragment = rhs.decodedFragment;
    decodedSchemeSpecificPart = rhs.decodedSchemeSpecificPart;
    _string = rhs._string;
}

URI& URI::operator=(const URI &rhs) {
    if (this != &rhs) {
        scheme = rhs.scheme;
        fragment = rhs.fragment;
        authority = rhs.authority;
        userInfo = rhs.userInfo;
        host = rhs.host;
        port = rhs.port;
        path = rhs.path;
        query = rhs.query;
        schemeSpecificPart = rhs.schemeSpecificPart;
        _hash = rhs._hash;
        decodedUserInfo = rhs.decodedUserInfo;
        decodedAuthority= rhs.decodedAuthority;
        decodedPath = rhs.decodedPath;
        decodedQuery = rhs.decodedQuery;
        decodedFragment = rhs.decodedFragment;
        decodedSchemeSpecificPart = rhs.decodedSchemeSpecificPart;
        _string = rhs._string;
    } 
    return *this;
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
    Parser p(this, _string);
    p.parse(true);
    return *this;
}

URI URI::normalize() { 
    URI r = URI::normalize(*this);
    return r;
}

URI URI::resolve(URI &uri) {
    return resolve(*this, uri);
}

URI URI::resolve(std::string str) {
    URI s = URI::create(str);
    URI r = resolve(s);
    return r;
}
URI URI::relativize(URI &uri) {
    URI r = relativize(*this, uri);
    return r;
}
/*
URL URI::toURL() throw (MalformedURLException) {
    URL u;
    return u;
}
*/

std::string URI::getScheme() { return scheme; }
bool URI::isAbsolute() { return (scheme.length() != 0); }
bool URI::isOpaque() { return path.length() == 0; }
std::string URI::getRawSchemeSpecificPart() {
    defineSchemeSpecificPart();
    return schemeSpecificPart;
}

std::string URI::getSchemeSpecificPart() {
    if (decodedSchemeSpecificPart.length() == 0) decodedSchemeSpecificPart = URI::decode(getRawSchemeSpecificPart());
    return decodedSchemeSpecificPart;
}

std::string URI::getRawAuthority() { return authority; }
std::string URI::getAuthority() {
    if (decodedAuthority.length() == 0) decodedAuthority = URI::decode(authority);
    return decodedAuthority;
}
std::string URI::getRawUserInfo() { return userInfo; }
std::string URI::getUserInfo() {
    if ((decodedUserInfo.length() == 0) && (userInfo.length() != 0))
        decodedUserInfo = URI::decode(userInfo);
    return decodedUserInfo;
}
std::string URI::getHost() { return host; }
int URI::getPort() { return port; }
std::string URI::getRawPath() { return path; }
std::string URI::getPath() {
    if ((decodedPath.length() == 0) && (path.length() != 0)) decodedPath = URI::decode(path);
    return decodedPath;
}
std::string URI::getRawQuery() { return query; }
std::string URI::getQuery() {
    if ((decodedQuery.length() == 0) && (query.length() != 0)) decodedQuery = URI::decode(query);
    return decodedQuery;
}
std::string URI::getRawFragment() { return fragment; }
std::string URI::getFragment() {
    if ((decodedFragment.length() == 0) && (fragment.length() != 0)) decodedFragment = URI::decode(fragment);
    return decodedFragment;
}
bool URI::equals(URI &that) {
    if (this == &that) return true;
    if (isOpaque() != that.isOpaque()) return false;
    if (!URI::equalIgnoringCase(scheme, that.scheme)) return false;
    if (!URI::equal(fragment, that.fragment)) return false;

    if (isOpaque()) return URI::equal(schemeSpecificPart, that.schemeSpecificPart);
    if (!URI::equal(path, that.path)) return false;
    if (!URI::equal(query, that.query)) return false;

    if (authority == that.authority) return true;
    if (host.length() > 0) {
        if (!URI::equal(userInfo, that.userInfo)) return false;
        if (!URI::equalIgnoringCase(host, that.host)) return false;
        if (port != that.port) return false;
    } else if (authority.length() > 0) {
        if (!URI::equal(authority, that.authority)) return false;
    } else if (authority != that.authority) return false;
    return true;
}
int URI::hashCode() {
    return 0;
}
int URI::compareTo(URI &that) {
    int c;
    if ((c = URI::compareIgnoringCase(scheme, that.scheme)) != 0) return c;
    if (isOpaque()) {
        if (that.isOpaque()) {
            if ((c = URI::compare(schemeSpecificPart, that.schemeSpecificPart)) != 0) return c;
            return URI::compare(fragment, that.fragment);
        }
        return 1;
    } else if (that.isOpaque()) return -1;
    if ((host.length() > 0) && (that.host.length() > 0)) {
        if ((c = URI::compare(userInfo, that.userInfo)) != 0) return c;
        if ((c = URI::compareIgnoringCase(host, that.host)) != 0) return c;
        if ((c = port - that.port) != 0) return c;
    } else {
        if ((c = URI::compare(authority, that.authority)) != 0) return c;
    }
    if ((c = URI::compare(path, that.path)) != 0) return c;
    if ((c = URI::compare(query, that.query)) != 0) return c;
    return URI::compare(fragment, that.fragment);
}
std::string URI::toString() {
    defineString();
    return _string;
}
std::string URI::toASCIIString() {
    defineString();
    return _string;
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
            if (URI::toLower(s[i]) != URI::toLower(t[i])) return false;
            i++;
            if (URI::toLower(s[i]) != URI::toLower(t[i])) return false;
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
            if (URI::toLower(s[i]) != URI::toLower(t[i])) return false;
        }
        return true;
    }
    return false;
}
int URI::hash(int h, std::string s) {
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
                int c = URI::toLower(s[i]) - URI::toLower(t[i]);
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

void URI::appendAuthority(stringstream &sb, std::string auth, std::string _userInfo, std::string _host, int _port) {
    if (_host.length() > 0) {
        sb << "//";
        if (_userInfo.length() > 0) {
            sb << (URI::quote(_userInfo, L_USERINFO, H_USERINFO));
            sb << "@";
        }
        bool needBrackets = ((_host.find(":") >= 0) && !URI::starts_with(_host, "[") && !URI::ends_with(_host, "]"));
        if (needBrackets) sb << "[";
        sb << _host;
        if (needBrackets) sb << "]";
        if (_port != -1) {
            sb << ":";
            sb << _port;
        }
    } else if (auth.length() > 0) {
        sb << "//";
        if (URI::starts_with(auth, "[")) {
            int end = auth.find("]");
            std::string doquote = auth, dontquote = "";
            if (end != std::string::npos && auth.find(":") != std::string::npos) {
                if (end == auth.length()) {
                    dontquote = auth; doquote = "";
                } else {
                    dontquote = auth.substr(0 , end + 1);
                    doquote = auth.substr(end + 1);
                }
            }
            sb << dontquote;
            sb << (URI::quote(doquote, L_REG_NAME | L_SERVER, H_REG_NAME | H_SERVER));
        } else {
            sb << (URI::quote(auth, L_REG_NAME | L_SERVER, H_REG_NAME | H_SERVER));
        }
    }
}

void URI::appendSchemeSpecificPart(stringstream &sb, std::string _opaquePart, std::string auth, std::string _userInfo, std::string _host, int _port, std::string path, std::string _query) {
    if (_opaquePart.length() > 0) {
        if (URI::starts_with(_opaquePart, "//[")) {
            int end =  _opaquePart.find("]");
            if (end != std::string::npos && _opaquePart.find(":") != std::string::npos) {
                std::string doquote, dontquote;
                if (end == _opaquePart.length()) {
                    dontquote = _opaquePart;
                    doquote = "";
                } else {
                    dontquote = _opaquePart.substr(0, end+ 1);
                    doquote = _opaquePart.substr(end + 1);
                }
                sb << (dontquote);
                sb << (URI::quote(doquote, L_URIC, H_URIC));
            }
        } else {
            sb << (URI::quote(_opaquePart, L_URIC, H_URIC));
        }
    } else {
        appendAuthority(sb, auth, _userInfo, _host, _port);
        if (path.length() > 0) sb << (URI::quote(path, L_PATH, H_PATH));
        if (_query.length() > 0) {
            sb << ("?");
            sb << (URI::quote(_query, L_URIC, H_URIC));
        }
    }
}

void URI::appendFragment(stringstream &sb, std::string fragment) {
    if (fragment.length() > 0) {
        sb << "#";
        sb << (URI::quote(fragment, L_URIC, H_URIC));
    }
}

std::string URI::toString(std::string _scheme, std::string _opaquePart, std::string _authority, std::string _userInfo, std::string _host, int _port, std::string _path, std::string _query, std::string _fragment) {
    stringstream sb;
    if (_scheme.length() > 0) {
        sb << _scheme;
        sb << ":";
    }
    appendSchemeSpecificPart(sb, _opaquePart, _authority, _userInfo, _host, _port, _path, _query);
    appendFragment(sb, _fragment);
    return sb.str();
}

void URI::defineSchemeSpecificPart() {
    if (schemeSpecificPart.length() > 0) return;
    stringstream sb;
    appendSchemeSpecificPart(sb, "", getAuthority(), getUserInfo(), host, port, getPath(), getQuery());
    if (sb.str().length() == 0) return;
    schemeSpecificPart = sb.str();
}

void URI::defineString() {
    if (_string.length() > 0) return;
    stringstream sb;
    if (scheme.length() > 0) {
        sb << scheme;
        sb << ":";
    }
    if (isOpaque()) sb << (schemeSpecificPart);
    else {
        if (host.length() > 0) {
            sb << "//";
            if (userInfo.length() > 0) {
                sb << userInfo;
                sb << "@";
            }
            bool needBrackets = ((host.find(":") != std::string::npos)  && !URI::starts_with(host, "[") && !URI::ends_with(host, "]"));
            if (needBrackets) sb << "[";
            sb << host;
            if (needBrackets) sb << "]";
            if (port != -1) {
                sb << ":";
                sb << port;
            }
        } else if (authority.length() > 0) {
            sb << "//";
            sb << authority;
        }
        if (path.length() > 0) sb << path;
        if (query.length() > 0) {
            sb << "?";
            sb << query;
        }
    }
    if (fragment.length() > 0) {
        sb << "#";
        sb << fragment;
    }
    _string = sb.str();
}

std::string URI::resolvePath(std::string base, std::string child, bool absolute) {
    int i = base.find_last_of('/');
    int cn = child.length();
    std::string path = "";
    if (cn == 0) {
        if (i >= 0) path = base.substr(0, i +1);
    } else {
        stringstream sb;
        if (i >= 0) sb << base.substr(0, i + 1);
        sb << child;
        path = sb.str();
    }
    std::string np = URI::normalize(path);
    return np;
}

URI URI::relativize(URI &base, URI &child) {
    if (child.isOpaque() || base.isOpaque()) return child;
    if (!URI::equalIgnoringCase(base.scheme, child.scheme) || !URI::equal(base.authority, child.authority)) return child;
    std::string bp = URI::normalize(base.path);
    std::string cp = URI::normalize(child.path);
     if (bp != cp) {
         if (!URI::ends_with(bp, "/")) bp += "/";
         if (!URI::starts_with(cp, bp)) return child;
     }
     URI v;
     v.path = cp.substr(bp.length());
     v.query = child.query;
     v.fragment = child.fragment;
     return v;
}

URI URI::resolve(URI &base, URI &child) {
    if (child.isOpaque() || base.isOpaque()) return child;
    if ((child.scheme.length() > 0) && (child.authority.length() > 0) && (child.path == "") && (child.fragment.length() > 0) && (child.query.length() == 0)) {
        if ((base.fragment.length() > 0) && (child.fragment == base.fragment)) return base;
        URI ru ;
        ru.scheme = base.scheme;
        ru.authority = base.authority;
        ru.userInfo = base.userInfo;
        ru.host = base.host;
        ru.port = base.port;
        ru.path = base.path;
        ru.fragment = child.fragment;
        ru.query = base.query;
        return ru;
    }
    if (child.scheme.length() > 0) return child;

    URI ru;
    ru.scheme = base.scheme;
    ru.query = child.query;
    ru.fragment = child.fragment;
    if (child.authority.length() == 0) {
        ru.authority = base.authority;
        ru.host = base.host;
        ru.userInfo = base.userInfo;
        ru.port = base.port;

        std::string cp = ((child.path.length() == 0) ? "": child.path);
        if ((cp.length() > 0) && (cp[0] == '/')) ru.path = child.path;
        else ru.path = resolvePath(base.path, cp, base.isAbsolute());
    } else {
        ru.authority = child.authority;
        ru.host = child.host;
        ru.userInfo = child.userInfo;
        ru.host = child.host;
        ru.port = child.port;
        ru.path = child.path;
    }
    return ru;
}

URI URI::normalize(URI &u) {
    if (u.isOpaque() || (u.path.length() == 0)) return u;
    std::string np = URI::normalize(u.path);
    if (np == u.path) return u;
    URI v;
    v.scheme = u.scheme;
    v.fragment = u.fragment;
    v.authority = u.authority;
    v.userInfo = u.userInfo;
    v.host = u.host;
    v.port = u.port;
    v.path = np;
    v.query = u.query;
    return v;
}

void URI::split(char *path, int pathlen, int* segs, int ns) {
    int end = pathlen - 1;
    int p = 0;
    int i = 0;
    while (p <= end) {
        if (path[p] != '/') break;
        path[p] = '\0';
        p++;
    }
    while (p <= end) {
        segs[i++] = p++;
        while (p <= end) {
            if (path[p++] != '/') continue;
            path[p - 1] = '\0';
            while (p <= end) {
                if (path[p] != '/') break;
                path[p++] = '\0';
            }
            break;
        }
    }
    if (i != ns) throw InternalError();
}

int URI::join(char *path, int pathlen, int* segs, int ns) {
    int end = pathlen - 1;
    int p = 0;
    if (path[p] == '\0') path[p++] = '/';
    for (int i = 0; i < ns; i++) {
        int q = segs[i];
        if (q == -1) continue;
        if (p == q) {
            while ((p <= end) && (path[p] != '\0')) p++;
            if (p <= end) path[p++] = '/';
        } else if (p < q) {
            while ((q <= end) && (path[q] != '\0')) path[p++] = path[q++];
            if (q <= end) path[p++] = '/';
        } else throw InternalError();
    }
    return p;
}

void URI::removeDots(char *path, int pathlen, int* segs, int ns) {
    int end = pathlen - 1;
    for (int i = 0; i < ns; i++) {
        int dots = 0;
        do {
            int p = segs[i];
            if (path[p] == '.') {
                if (p == end) {
                    dots = 1; break;
                } else if (path[p + 1] == '\0') {
                    dots = 1; break;
                } else if ((path[p + 1] == '.') && ((p + 1 == end) || (path[p + 2] == '\0'))) {
                    dots = 2; break;
                }
            }
            i++;
        } while (i < ns);
        if ((i > ns) || (dots == 0)) break;
        if (dots == 1) segs[i] = -1;
        else {
            int j;
            for (j = i - 1; j >= 0; j--) {
                if (segs[j] != -1) break;
            }
            if (j >= 0) {
                int q = segs[j];
                if (!((path[q] == '.') && (path[q + 1] == '.') && (path[q + 2] == '\0'))) {
                    segs[i] = -1;
                    segs[j] = -1;
                }
            }
        }
    }
}

void URI::maybeAddLeadingDot(char *path, int pathlen, int* segs, int ns) {
    if (path[0] == '\0') return;
    int f = 0;
    while (f < ns) {
        if (segs[f] >= 0) break;
        f++;
    }
    if ((f >= ns) || (f == 0)) return;
    int p = segs[f];
    while ((p < pathlen && path[p] != ':') && (path[p] != '\0')) p++;
    if (p >= pathlen || path[p] == '\0') return;
    path[0] = '.';
    path[1] = '\0';
    segs[0] = 0;
}

int URI::needsNormalization(std::string path) {
    bool normal = true;
    int ns = 0; int end = path.length() - 1; int p = 0;
    while (p <= end) {
        if (path[p] != '/') break;
        p++;
    }
    if (p > 1) normal = false;
    while (p <= end) {
        if ((path[p] == '.')
                && ((p == end)
                    || ((path[p + 1] == '/')
                        || ((path[p + 1] == '.')
                            && ((p + 1 == end)
                                || (path[p + 2] == '/')))))) {
            normal = false;
        }
        ns++;
        while (p <= end) {
            if (path[p++] != '/') continue;
            while (p <= end) {
                if (path[p] != '/') break;
                normal = false;
                p++;
            }
            break;
        }
    }
    return ((normal) ? -1 : ns);
}

bool URI::starts_with(std::string requestUri, std::string pattern) {
    int to = 0;
    int po = 0;
    int pc = pattern.length();
    if (requestUri.length() - pc < 0) return false;
    while (--pc >= 0) {
        if (requestUri[to++] != pattern[po]) return false;
    }
    return true;
}

bool URI::ends_with(std::string requestUri, std::string pattern) {
    int toffset = requestUri.length() - pattern.length();
    int to = toffset;
    int po = 0;
    int pc = pattern.length();
    if ((toffset < 0) || (toffset > requestUri.length() - pc)) return false;
    while (--pc >= 0) {
        if (requestUri[to++] != pattern[po++]) return false;
    }
    return true;
}

std::string URI::normalize(std::string ps) {
    int ns = URI::needsNormalization(ps);
    if (ns < 0) return ps;
    char path[ps.length()];
    strcpy(path, ps.c_str());
    int segs[ns];
    URI::split(path, ps.length(), segs, ns);
    URI::removeDots(path, ps.length(), segs, ns);
    URI::maybeAddLeadingDot(path, ps.length(), segs, ns);
    std::string s(path, URI::join(path, ps.length(), segs, ns));
    if (s == ps) return ps;
    return s;
}

long URI::lowMask(int first, int last) {
    long m = 0;
    int f = std::max<int>(std::min<int>(first, 63), 0);
    int l = std::max<int>(std::min<int>(last, 63), 0);
    for (int i = f; i <= l; i++) m |= (1L << i);
    return m;
}

long URI::lowMask(std::string chars) {
    int n = chars.length();
    long m = 0;
    for (int i = 0; i < n; i++) {
        char c = chars[i];
        if (c < 64) m |= (1L << c);
    }
    return m;
}

long URI::highMask(std::string chars) {
    int n = chars.length();
    long m = 0;
    for (int i = 0; i < n; i++) {
        char c = chars[i];
        if ((c >= 64) && (c < 128)) m |= (1L << (c - 64));
    }
    return m;
}

long URI::highMask(int first, int last) {
    long m = 0;
    int f = std::max<int>(std::min<int>(first, 127), 64) - 64;
    int l = std::max<int>(std::min<int>(last, 127), 64) - 64;
    for (int i = f; i <= l; i++) m |= (1L << i);
    return m;
}

bool URI::match(char c, long lMask, long hMask) {
    if (c == 0) return false;
    if (c < 64) return ((1L << c) & lMask) != 0;
    if (c < 128) return ((1L << (c - 64)) & hMask) != 0;
    return false;
}

void URI::appendEscape(stringstream &ss, byte b) {
    ss << '%';
    ss << (hexDigits[(b >> 4) & 0x0f]);
    ss << (hexDigits[(b >> 0) & 0x0f]);
}

bool URI::isISOControl(char c) {
    return (c >= 0x0000 && c <= 0x001F) || (c >= 0x007F && c <= 0x009F);
}

void URI::appendEncoded(stringstream &ss, char c) {
    int b = c & 0xff;
    if (b >= 0x80) URI::appendEscape(ss, (byte)b);
    else ss << c;
}

std::string URI::quote(std::string s, long lMask, long hMask) {
    int n = s.length();
    stringstream ss ;
    bool allowNonASCII = ((lMask & L_ESCAPED) != 0);
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (c < 0x0080) {
            if (!URI::match(c, lMask, hMask)) {
                if (ss.str().length() == 0) ss << s.substr(0, i);
                URI::appendEscape(ss, (byte)c);
            } else if (ss.str().length() > 0) ss << c;
        } else if (allowNonASCII && (isspace(c) || URI::isISOControl(c))) {
            if (ss.str().length() == 0) ss << s.substr(0, i);
            URI::appendEncoded(ss, c);
        } else {
            if (ss.str().length() > 0) ss << c;
        }
    }
    if (ss.str().length() == 0) return s;
    return ss.str();
}

std::string URI::encode(std::string s) {
    int n = s.length();
    if (n == 0) return s;
    for (int i = 0;;) {
        if (s[i] >= 0x0080) break;
        if (++i >= n) return s;
    }
    stringstream ss;
    for (int i = 0; i < n; i++) {
        int b = s[i] & 0xff;
        if (b >= 0x80) URI::appendEscape(ss, (byte)b);
        else ss << b;
    }
    return ss.str();
}

int URI::decode(char c) {
    if ((c >= '0') && (c <= '9')) return c - '0';
    if ((c >= 'a') && (c <= 'f')) return c - 'a' + 10;
    if ((c >= 'A') && (c <= 'F')) return c - 'A' + 10;
    return -1;
}

byte URI::decode(char c1, char c2) {
    return (byte) ( ((URI::decode(c1) & 0xf) << 4)| ((URI::decode(c2) & 0xf) << 0));
}

std::string URI::decode(std::string s) {
    if (s.length() == 0) return s;
    int n = s.length();
    if (s.find('%') == std::string::npos) return s;

}

URI::Parser::Parser(URI *u, std::string s) : uri(u) {
    input = s;
    uri->_string = s;
    requireServerAuthority = false;
    ipv6byteCount = 0;
}

void URI::Parser::fail(std::string reason) throw(URISyntaxException) {
    throw URISyntaxException(input, reason);
}

void URI::Parser::fail(std::string reason, int p) throw(URISyntaxException) {
    throw URISyntaxException(input, reason, p);
}

void URI::Parser::failExpecting(std::string expected, int p) throw(URISyntaxException) {
    fail("Expected " + expected, p);
}

void URI::Parser::failExpecting(std::string expected, std::string prior, int p) throw(URISyntaxException) {
    stringstream ss ;
    ss << "Expected " << expected << " following " << prior;
    std::string s = ss.str();
    fail(s, p);
}

std::string URI::Parser::substring(int start, int end) {
    return input.substr(start, end - start);
}

char URI::Parser::charAt(int p) {
    return input[p];
}

bool URI::Parser::at(int start, int end, char c) {
    return (start < end) && (charAt(start) == c);
}

bool URI::Parser::at(int start, int end, std::string s) {
    int p = start;
    int sn = s.length();
    if (sn > end - p) return false;
    int i = 0;
    while (i < sn) {
        if (charAt(p++) != s[i]) break;
        i++;
    }
    return (i == sn);
}

int URI::Parser::scan(int start, int end, char c) {
    if ((start < end) && (charAt(start) == c)) return start + 1;
    return start;
}

int URI::Parser::scan(int start, int end, std::string err, std::string stop) {
    int p = start;
    while (p < end) {
        char c = charAt(p);
        if (err.find(c) != std::string::npos) return -1;
        if (stop.find(c) != std::string::npos) break; 
        p++;
    }
    return p;
}

int URI::Parser::scanEscape(int start, int n, char first) throw (URISyntaxException) {
    int p = start; char c = first;
    if (c == '%') {
        if ((p + 3 <= n) && URI::match(charAt(p + 1), L_HEX, H_HEX) && URI::match(charAt(p + 2), L_HEX, H_HEX)) return p + 3;
        fail("Malformed escape pair", p);
    } else if ((c > 128) && !isspace(c) && !URI::isISOControl(c)) {
        return p + 1;
    }
    return p;
}

int URI::Parser::scan(int start, int n, long lMask, long hMask) throw (URISyntaxException) {
    int p = start;
    while (p < n) {
        char c = charAt(p);
        if (URI::match(c, lMask, hMask)) {
            p++; continue;
        }
        if ((lMask & L_ESCAPED) != 0) {
            int q = scanEscape(p, n, c);
            if (q > p) { 
                p = q;
                continue;
            }
        }
        break;
    }
    return p;
}

void URI::Parser::checkChars(int start, int end, long lMask, long hMask, std::string what) throw (URISyntaxException) {
    int p = scan(start, end, lMask, hMask);
    if (p < end) fail("Illegal character in " + what, p);
}

void URI::Parser::checkChar(int p, long lMask, long hMask, std::string what) throw (URISyntaxException) {
    checkChars(p, p + 1, lMask, hMask, what);
}

void URI::Parser::parse(bool rsa) throw (URISyntaxException) {
    requireServerAuthority = rsa;
    int ssp; 
    int n = input.length();
    int p = scan(0, n, "/?#", ":");
    if ((p >= 0) && at(p, n, ':')) {
        if (p == 0) failExpecting("scheme name", 0);
        checkChar(0, L_ALPHA, H_ALPHA, "scheme name");
        checkChars(1, p, L_SCHEME, H_SCHEME, "scheme name");
        uri->scheme = substring(0, p);
        p++;
        ssp = p;
        if (at(p, n, '/')) p = parseHierarchical(p, n);
        else {
            int q = scan(p, n, "", "#");
            if (q <= p) failExpecting("scheme-specific part", p);
            checkChars(p, q, L_URIC, H_URIC, "opaque part");
            p = q;
        }
    } else {
        ssp = 0;
        p = parseHierarchical(0, n);
    } 
    uri->schemeSpecificPart = substring(ssp, p);
    if (at(p, n, '#')) {
        checkChars(p + 1, n, L_URIC, H_URIC, "fragment");
        uri->fragment = substring(p + 1, n);
        p = n;
    }
    if (p < n) fail("end of URI", p);
}

int URI::Parser::parseHierarchical(int start, int n) throw (URISyntaxException) {
    int p = start;
    if (at(p, n, '/') && at(p + 1, n, '/')) {
        p += 2;
        int q = scan(p, n, "", "/?#");
        if (q > p) p = parseAuthority(p, q);
        else if (q < n) {
            ;
        } else failExpecting("authority", p);
    }
    int q = scan(p, n, "", "?#");
    checkChars(p, q, L_PATH, H_PATH, "path");
    uri->path = substring(p, q);
    p = q;
    if (at(p, n, '?')) {
        p++;
        q = scan(p, n, "", "#");
        checkChars(p, q, L_URIC, H_URIC, "query");
        uri->query = substring(p, q);
        p = q;
    }
    return p;
}

int URI::Parser::parseAuthority(int start, int n) throw (URISyntaxException) {
    URISyntaxException ex;
    bool thrownError = false;
    int p = start;
    int q = p;
    bool serverChars, regChars;
    if (scan(p, n, "", "]") > p) {
        serverChars = (scan(p, n, L_SERVER_PERCENT, H_SERVER_PERCENT) == n);
    } else serverChars = (scan(p, n, L_SERVER, H_SERVER) == n);
    regChars = (scan(p, n, L_REG_NAME, H_REG_NAME) == n);
    if (regChars && !serverChars) {
        uri->authority = substring(p, n); return n;
    }
    if (serverChars) {
        try {
            q = parseServer(p, n);
            if (q < n) failExpecting("end of authority", q);
            uri->authority = substring(p, n);
        } catch (const URISyntaxException &e) {
            uri->userInfo = "";
            uri->host = "";
            uri->port = -1;
            if (requireServerAuthority) throw e;
            else {
                thrownError = true;
                ex = e;
                q = p;
            }
        }
    }
    if (q < n) {
        if (regChars) uri->authority = substring(p, n);
        else if (thrownError) throw ex;
        else fail("Illegal character in authority", q);
    }
    return n;
}

int URI::Parser::parseServer(int start, int n) throw(URISyntaxException) {
    int p = start;
    int q;
    q = scan(p, n, "/?#", "@");
    if ((q >= p) && at(q, n, '@')) {
        checkChars(p, q, L_USERINFO, H_USERINFO, "user info");
        uri->userInfo = substring(p, q);
        p = q + 1;
    }
    if (at(p, n, '[')) {
        p++;
        q = scan(p, n, "/?#", "]");
        if ((q > p) && at(q, n, ']')) {
            int r = scan (p, q, "", "%");
            if (r > p) {
                parseIPv6Reference(p, r);
                if (r+1 == q) fail ("scope id expected");
                checkChars (r+1, q, L_ALPHANUM, H_ALPHANUM, "scope id");
            } else {
                parseIPv6Reference(p, q);
            }
            uri->host = substring(p-1, q+1);
            p = q + 1;
        } else failExpecting("closing bracket for IPv6 address", q);
    } else {
        q = parseIPv4Address(p, n);
        if (q <= p) q = parseHostname(p, n);
        p = q;
    }
    if (at(p, n, ':')) {
        p++;
        q = scan(p, n, "", "/");
        if (q > p) {
            checkChars(p, q, L_DIGIT, H_DIGIT, "port number");
            try {
                uri->port = Integer::parseInt(substring(p, q));
            } catch (...) {
                fail("Malformed port number", p);
            }
            p = q;
        }
    }
    if (p < n) failExpecting("port number", p);
    return p;
}

int URI::Parser::scanByte(int start, int n) throw (URISyntaxException) {
    int p = start;
    int q = scan(p, n, L_DIGIT, H_DIGIT);
    if (q <= p) return q;
    if (Integer::parseInt(substring(p, q)) > 255) return p;
    return q;
}

int URI::Parser::scanIPv4Address(int start, int n, bool strict) throw (URISyntaxException) {
    int p = start; int q;
    int m = scan(p, n, L_DIGIT | L_DOT, H_DIGIT | H_DOT);
    if ((m <= p) || (strict && (m != n))) return -1;
    for (;;) {
        if ((q = scanByte(p, m)) <= p) break;   p = q;
        if ((q = scan(p, m, '.')) <= p) break;  p = q;
        if ((q = scanByte(p, m)) <= p) break;   p = q;
        if ((q = scan(p, m, '.')) <= p) break;  p = q;
        if ((q = scanByte(p, m)) <= p) break;   p = q;
        if ((q = scan(p, m, '.')) <= p) break;  p = q;
        if ((q = scanByte(p, m)) <= p) break;   p = q;
        if (q < m) break;
        return q;
    }
    fail("Malformed IPv4 address", q);
    return -1;
}

int URI::Parser::takeIPv4Address(int start, int n, std::string expected) throw (URISyntaxException) {
    int p = scanIPv4Address(start, n, true);
    if (p <= start) failExpecting(expected, start);
    return p;
}

int URI::Parser::parseIPv4Address(int start, int n) {
    int p;
    try {
        p = scanIPv4Address(start, n, false);
    } catch (const URISyntaxException &x) {
        return -1;
    } catch (...) {
        return -1;
    }
    if (p > start && p < n) {
        if (charAt(p) != ':')  p = -1;
    }
    if (p > start) uri->host = substring(start, p);
    return p;
}

int URI::Parser::parseHostname(int start, int n) throw (URISyntaxException) {
    int p = start; int q; int l = -1;
    do {
        q = scan(p, n, L_ALPHANUM, H_ALPHANUM);
        if (q <= p) break;
        l = p;
        if (q > p) {
            p = q;
            q = scan(p, n, L_ALPHANUM | L_DASH, H_ALPHANUM | H_DASH);
            if (q > p) {
                if (charAt(q - 1) == '-') fail("Illegal character in hostname", q - 1);
                p = q;
            }
        }
        q = scan(p, n, '.');
        if (q <= p) break;
        p = q;
    } while (p < n);
    if ((p < n) && !at(p, n, ':')) fail("Illegal character in hostname", p);
    if (l < 0) failExpecting("hostname", start);
    if (l > start && !URI::match(charAt(l), L_ALPHA, H_ALPHA)) fail("Illegal character in hostname", l);
    uri->host = substring(start, p);
    return p;
}

int URI::Parser::parseIPv6Reference(int start, int n) throw (URISyntaxException) {
    int p = start; int q; bool compressedZeros = false;
    q = scanHexSeq(p, n);
    if (q > p) {
        p = q;
        if (at(p, n, "::")) {
            compressedZeros = true;
            p = scanHexPost(p + 2, n);
        } else if (at(p, n, ':')) {
            p = takeIPv4Address(p + 1,  n, "IPv4 address");
            ipv6byteCount += 4;
        }
    } else if (at(p, n, "::")) {
        compressedZeros = true;
        p = scanHexPost(p + 2, n);
    }
    if (p < n) fail("Malformed IPv6 address", start);
    if (ipv6byteCount > 16) fail("IPv6 address too long", start);
    if (!compressedZeros && ipv6byteCount < 16) fail("IPv6 address too short", start);
    if (compressedZeros && ipv6byteCount == 16) fail("Malformed IPv6 address", start);
    return p;
}

int URI::Parser::scanHexPost(int start, int n) throw (URISyntaxException) {
    int p = start; int q;
    if (p == n) return p;
    q = scanHexSeq(p, n);
    if (q > p) {
        p = q;
        if (at(p, n, ':')) {
            p++;
            p = takeIPv4Address(p, n, "hex digits or IPv4 address");
            ipv6byteCount += 4;
        }
    } else {
        p = takeIPv4Address(p, n, "hex digits or IPv4 address");
        ipv6byteCount += 4;
    }
    return p;
}

int URI::Parser::scanHexSeq(int start, int n) throw (URISyntaxException) {
    int p = start; int q;
    q = scan(p, n, L_HEX, H_HEX);
    if (q <= p) return -1;
    if (at(q, n, '.')) return -1;
    if (q > p + 4) fail("IPv6 hexadecimal digit sequence too long", p);
    ipv6byteCount += 2;
    p = q;
    while (p < n) {
        if (!at(p, n, ':')) break;
        if (at(p + 1, n, ':')) break;
        p++;
        q = scan(p, n, L_HEX, H_HEX);
        if (q <= p) failExpecting("digits for an IPv6 address", p);
        if (at(q, n, '.')) {
            p--;
            break;
        }
        if (q > p + 4) fail("IPv6 hexadecimal digit sequence too long", p);
        ipv6byteCount += 2;
        p = q;
    }
    return p;
}
