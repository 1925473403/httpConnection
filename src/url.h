#include <iostream>
#include <string>

#include "STokenizer.h"
using namespace std;

#ifndef URL_H
#define URL_H
class servicediscovery {
    void trim(string &s) {
        int is = 0, ei = 0;
        for (is = 0; is < s.length(); is++)
            if (s[is] == ' ') continue;
            else break;
        for (ei = s.length() - 1; ei >=is; ei--)
            if (s[ei] == ' ') continue;
            else break;
        if (is != 0) {
            size_t len = ei - is;
            for (int i = 0; i < len; i++)
                s[i] = s[is++];
            s[len] = 0;
        }
    }
    void trim(char *s) {
        int is = 0, ei = 0;
        for (is = 0; is < strlen(s); is++)
            if (s[is] == ' ') continue;
            else break;
        for (ei = strlen(s) - 1; ei >=is; ei--)
            if (s[ei] == ' ') continue;
            else break;
        if (is != 0) {
            size_t len = ei - is;
            for (int i = 0; i < len; i++)
                s[i] = s[is++];
            s[len] = 0;
        }
    }
    public:
    unordered_multimap<string, std::pair<string, string>> services;
        servicediscovery() {
            std::cout << "servicediscovery ctor" << std::endl;
            std::ifstream ifs("/etc/services", std::ifstream::in);
            while (!ifs.eof()) {
                char l[1024];
                ifs.getline(l, 1024);
                trim(l);
                if (strlen(l) == 0 || l[0] == '#') continue;
                char *p = l, *r = p, *q = p + strlen(l);
                string key= "", value = "";
                while (p < q) {
                    if (*p != ' '&& *p != '\t') p++;
                    else {
                        if (key.size() == 0) {
                            key.assign(r, p - r);
                        } else {
                            if (value.size() == 0) {
                                while (*p == ' ') p++;
                                r = p;
                                while (*p != ' ' && *p != '\t') p++;
                                value.assign(r, p - r);
                                STokenizer<string, char> st((char *)value.c_str(), value.length(), "/");
                                string v1 = st.getnext();
                                string v2 = st.getnext();
                                services.insert(std::make_pair(key, std::make_pair(v1, v2)));
                                break;
                            }
                        }
                    }
                }
            }
        }
        size_t size() const { return services.size(); }
        servicediscovery(const servicediscovery& rhs) {
            services.clear();
            for (auto it = rhs.services.cbegin(); it != rhs.services.cend(); it++) {
                services.insert(std::make_pair(it->first, std::make_pair(it->second.first, it->second.second)));
            }
        }
        servicediscovery& operator=(const servicediscovery &rhs) {
            if (this == &rhs) return *this;
            services.clear();
            for (auto it = rhs.services.cbegin(); it != rhs.services.cend(); it++)
                services.insert(std::make_pair(it->first, std::make_pair(it->second.first, it->second.second)));
            return *this;
        }
        std::string getport(string &p) {
            for (auto it = services.begin(); it != services.end(); it++) {
                if (it->first == p) return it->second.first;
            }
            return string("0");
        }
};
class Url {
    string _protocol;
    string _host;
    string _port;
    string _file;
    bool isValidProtocol(string &protocol) {
        int len = protocol.length();
        if (len < 1) return false;
        if (!isalpha(protocol[0])) return false;
        for (int i = 1; i < len; i++) {
            if (!isalnum(protocol[i]) && protocol[i] != '.' && protocol[i] != '+' && protocol[i] != '-') return false;
        }
        return true;
    }
    std::string _original;
    public:
        servicediscovery sd;
        int getport() {
            if (_port.size() > 0) return atoi(_port.c_str());
            if (sd.size()) {
                _port = sd.getport(_protocol);
            }
            return atoi(_port.c_str());
        }
        string original() const { return _original; }
        Url(const Url &rhs) {
            _original = rhs.original();
            _host = rhs.host();
            _protocol = rhs.protocol();
            _port = rhs.port();
            _file = rhs.path();
            sd = rhs.sd;
        }
        Url& operator=(const Url& rhs) {
            if (this == &rhs) return *this;
            _original = rhs.original(); _host = rhs.host(); _protocol = rhs.protocol(); _port = rhs.port(); _file = rhs.path();
            sd = rhs.sd;
        }
        void setpath(string s) { _file.assign(s); }
        Url(string &str):_protocol(""), _host(""), _file("") {
            _original.assign(str);
            std::string newProtocol = "";
            int i, limit, c;
            int start = 0;
            bool aRef = false, isRelative = false;
            try {
                limit = _original.length();
                while ((limit > 0) && (str[limit - 1] == ' ')) limit --;
                while ((start < limit) && (str[start] == ' ')) start++;
                if (str.find("url:") != string::npos) start += 4;
                if (start < _original.length() && str[start] == '#') aRef = true;
                for (int i = start; !aRef && (i < limit) && (str[i] != '/'); i++) {
                    if (_original[i] == ':') {
                        string s = _original.substr(start, i);
                        if (isValidProtocol(s)) {
                            newProtocol = s; start = i + 1;
                        }
                        break;
                    }
                }
                _protocol = newProtocol;
                if (_protocol.length() == 0) throw MalformedURLException("unknown protocol: ", _original);
                assert(str[start] == '/' && str[start+1] == '/'); start+= 2;
                for (int i = start; !aRef && (i < limit) && (str[i] != '/'); i++) {
                    if (_original[i+1] == '/') {
                        _host = _original.substr(start, i  - start + 1);
                        start = i+1;
                        break;
                    }
                }
                assert(str[start] == '/'); start ++;
                _file = str.substr(start);
            } catch (...) {
                throw;
            }

        }
        string port() const { return _port; }
        string host() const { return _host; }
        string protocol() const { return _protocol; }
        string path() const { return _file; }
};
#endif


