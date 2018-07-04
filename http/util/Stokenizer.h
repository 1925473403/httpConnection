#include "HttpException.h"
#ifndef STOKENIZER_H
#define STOKENIZER_H
template <typename T>
class Stokenizer {
    T str;
    const char *m_del;
    int pos;
    int prev;
    public:
    Stokenizer(T s, const char *del = " ") : pos(0), prev(0), str(s), m_del(del) { }
    bool hasnext() { 
        if (pos != std::string::npos) return str.find(m_del, pos) != string::npos; 
        else return false;
    }
    std::string getnext() {
        if (pos != std::string::npos) {
            prev = pos;
            pos = str.find(m_del, pos);
            if (pos != std::string::npos) return str.substr(prev, pos++ - prev);
            else return str.substr(prev);
        } else return "";
    }
};
#endif
