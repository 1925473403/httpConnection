#include <iostream>
#include <string>
using namespace std;

#ifndef STOKENIZER_H
#define STOKENIZER_H
static const char *delimiter = "\r\n";
template<class T, class U>
class STokenizer {
    int m_prev, m_pos;
    T m_str;
    const char *m_del;
    int incr(int ) { int old = m_pos; m_pos += strlen(m_del); return old; }
    public:
    int getsize() const { return m_prev; }
    STokenizer(U* str, int len, const char *del=delimiter) { m_pos = 0; m_prev = 0; m_str.assign((U*)str, len); m_del = del; }
    bool hasnext() { return m_str.find((U *)delimiter, m_pos) != string::npos; }
    T getall() { return m_str.substr(m_pos); }
    T getnext() { 
        m_prev = m_pos;
        m_pos = m_str.find((U *)m_del, m_pos);
        if (m_pos != string::npos) return m_str.substr(m_prev, incr(m_pos) - m_prev);
        else return m_str.substr(m_prev);
    }
};

#endif
