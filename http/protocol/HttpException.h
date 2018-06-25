#include <string.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <stdarg.h>
using namespace std;
#ifndef HTTPEXCEPTION_H
#define HTTPEXCEPTION_H
class IOException : public std::exception {
    public:
        IOException() { }
        virtual ~IOException() { }
        IOException(std::string &str) {
            snprintf(m_reason, 511, "%s", str.c_str());
        }
        IOException(const char *str) {
            if (str) {
                snprintf(m_reason, 511, "%s", str);
            }
        }
        virtual const char *what() const throw() { return m_reason; }
        virtual int describe(char *apStr, int len) {
            if ((apStr) && len > 1)
                return snprintf(apStr, len - 1, "%s", m_reason);
            return 0;
        }
    protected:
        char m_reason[512];
};
class MalformedURLException : public std::exception {
    public:
        MalformedURLException(std::string &str) {
            snprintf(m_reason, 511, "%s", str.c_str());
        }
        MalformedURLException(const char *str, const std::string &s) {
            snprintf(m_reason, 511, "%s %s", str, s.c_str());
        }
        const char *what() const throw() { return m_reason; }
        int describe(char *apStr, int len) {
            if ((apStr) && len > 1)
                return snprintf(apStr, len - 1, "%s", m_reason);
            return 0;
        }
    private:
        char m_reason[512];
};

class IllegalArgumentException:public IOException {
    public:
        IllegalArgumentException(std::string str) : IOException(str) { }
        IllegalArgumentException(const char* str, ...) {
            va_list args;
            va_start(args, str);
            vsnprintf(m_reason, 511, str, args);
            va_end(args);
        }
};

class IndexOutOfBoundsException:public std::exception {
    char m_reason[512];
    public:
        IndexOutOfBoundsException() { }
        ~IndexOutOfBoundsException() { }
        IndexOutOfBoundsException(std::string str) { snprintf(m_reason, 511, "%s", str.c_str()); }
        IndexOutOfBoundsException(const char *str,...) {
            va_list args;
            va_start(args, str);
            vsnprintf(m_reason, 511, str, args);
            va_end(args);
        }
        const char *what() const throw() { return "IndexOutOfBoundsException"; }
        int describe(char *apStr, int len) {
            if (apStr && (len > 20)) return snprintf(apStr, len -1, "IndexOutOfBoundsException");
            return 0;
        }
};
class NoHttpResponseException : public IOException {
    public:
    NoHttpResponseException(std::string str):IOException(str) { }
    NoHttpResponseException(const char *str,...) {
        va_list args;
        va_start(args, str);
        vsnprintf(m_reason, 511, str, args);
        va_end(args);
    }
};
class HttpException : std::exception {
    protected:
    char m_reason[512];
    public:
    HttpException() { }
    virtual ~HttpException() { }
    HttpException(std::string str) { snprintf(m_reason, 511, "%s", str.c_str()); }
    HttpException(const HttpException &rhs) {
        strcpy(m_reason, rhs.m_reason);
    }
    HttpException& operator=(const HttpException &rhs) {
        if (this != &rhs) {
            strcpy(m_reason, rhs.m_reason);
        }
        return *this;
    }
    HttpException(std::string str, std::exception &e) {
        snprintf(m_reason, 511, "%s", str.c_str());
        char errMsg[512] = { 0 };
        snprintf(errMsg, 511, "%s", e.what());
        snprintf(m_reason + strlen(m_reason), 511, " %s", errMsg);
    }
    const char *what() const throw() { return m_reason; }
    int describe(char *apStr, int len) {
        if (apStr && (len > 1)) return snprintf(apStr, len -1, "%s", m_reason);
        return 0;
    }
};
class MethodNotSupportedException : public HttpException {
    public:
    MethodNotSupportedException(std::string str):HttpException(str) { }
    MethodNotSupportedException(std::string str, std::exception &e):HttpException(str, e) { }
    MethodNotSupportedException(const char *str,...) {
        va_list args;
        va_start(args, str);
        vsnprintf(m_reason, 511, str, args);
        va_end(args);
    }
};
class MalformedChunkCodingException : public IOException {
    public:
    MalformedChunkCodingException() : IOException() { }
    MalformedChunkCodingException(std::string s):IOException(s) { }
    MalformedChunkCodingException(const char *str, ...) {
        va_list args;
        va_start(args, str);
        vsnprintf(m_reason, 511, str, args);
        va_end(args);
    }
};
class ParseException : public IOException {
    public:
    ParseException() : IOException() { }
    ParseException(std::string s):IOException(s) { }
    ParseException(const char *str, ...) {
        va_list args;
        va_start(args, str);
        vsnprintf(m_reason, 511, str, args);
        va_end(args);
    }
};
class UnsupportedOperationException : public IOException {
    public:
    UnsupportedOperationException() : IOException() { }
    UnsupportedOperationException(std::string s):IOException(s) { }
    UnsupportedOperationException(const char *str, ...) {
        va_list args;
        va_start(args, str);
        vsnprintf(m_reason, 511, str, args);
        va_end(args);
    }
};
class NoSuchElementException : public IOException {
    public:
        NoSuchElementException() : IOException() { }
        NoSuchElementException(std::string s):IOException(s) { }
        NoSuchElementException(const char *str, ...) {
            va_list args;
            va_start(args, str);
            vsnprintf(m_reason, 511, str, args);
            va_end(args);
        }
};
class IllegalStateException : public IOException {
    public:
        IllegalStateException() : IOException() { }
        IllegalStateException(std::string s):IOException(s) { }
        IllegalStateException(const char *str, ...) {
            va_list args;
            va_start(args, str);
            vsnprintf(m_reason, 511, str, args);
            va_end(args);
        }
};
#endif
