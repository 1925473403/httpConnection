#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
using namespace std;
#ifndef HTTPEXCEPTION_H
#define HTTPEXCEPTION_H
class IOException : public std::exception {
    public:
        IOException() { }
        virtual ~IOException() { }
        IOException(const IOException &rhs) {
            strcpy(m_reason, rhs.m_reason);
        }
        IOException& operator=(const IOException &rhs) {
            if (this != &rhs) {
                strcpy(m_reason, rhs.m_reason);
            }
            return *this;
        }
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
class HttpHost ;
class SocketException : public IOException {
    public:
    SocketException(const char *str) : IOException(str) { }
    SocketException() { }
};
class ConnectException : public SocketException {
    public:
    ConnectException(const char *str) :SocketException(str) { }
    ConnectException() { }
};
/*
class HttpHostConnectException : public IOException {
    HttpHost *host;
=======

class SocketException : public IOException {
    public:
        SocketException() : IOException() { }
        SocketException(std::string &s): IOException(s) { }
        SocketException(const char *s) : IOException(s) { }
};

class ConnectException : public SocketException {
    public:
    ConnectException(std::string &s) : SocketException(s) { }
    ConnectException(const char *str) : SocketException(str) { }
    ConnectException() : SocketException() { }
};

class ConnectionResetException : public IOException {
>>>>>>> 8f0a1ebc7b17dfa789fa5de46f12b6865dedf9ec
    public:
    ConnectionResetException() : IOException() { }
    ConnectionResetException(std::string s) : IOException(s) { }
    ConnectionResetException(const char *str, ...) {
            va_list args;
            va_start(args, str);
            vsnprintf(m_reason, 511, str, args);
            va_end(args);
    }
};
<<<<<<< HEAD
*/

class SecurityException : public IOException {
    public:
    SecurityException() : IOException() { }
    SecurityException(std::string s) : IOException(s) { }
    SecurityException(const char *str, ...) {
            va_list args;
            va_start(args, str);
            vsnprintf(m_reason, 511, str, args);
            va_end(args);
    }
};
class UnknownHostException : public IOException {
    public:
    UnknownHostException() : IOException() { }
    UnknownHostException(std::string s) : IOException(s) { }
    UnknownHostException(const char *str, ...) {
            va_list args;
            va_start(args, str);
            vsnprintf(m_reason, 511, str, args);
            va_end(args);
    }
};
class NumberFormatException : public IOException {
    public:
    NumberFormatException() : IOException() { }
    NumberFormatException(std::string s) : IOException(s) { }
    NumberFormatException(const char *str, ...) {
            va_list args;
            va_start(args, str);
            vsnprintf(m_reason, 511, str, args);
            va_end(args);
    }
};
class InternalError : public IOException {
    public:
        InternalError() : IOException() { }
        InternalError(std::string s) : IOException(s) { }
        InternalError(const char *str, ...) {
            va_list args;
            va_start(args, str);
            vsnprintf(m_reason, 511, str, args);
            va_end(args);
        }
};
class NullPointerException : public IOException {
    public:
        NullPointerException() : IOException() { }
        NullPointerException(std::string s):IOException(s) { }
        NullPointerException(const char *str, ...) {
            va_list args;
            va_start(args, str);
            vsnprintf(m_reason, 511, str, args);
            va_end(args);
        }
};

class IllegalArgumentException:public IOException {
    public:
        IllegalArgumentException() : IOException() { }
        IllegalArgumentException(std::string str) : IOException(str) { }
        IllegalArgumentException(const char* str, ...) {
            va_list args;
            va_start(args, str);
            vsnprintf(m_reason, 511, str, args);
            va_end(args);
        }
};

class URISyntaxException : public IOException {
    std::string input;
    int index;
    public:
        URISyntaxException() : IOException() { }
        URISyntaxException(const URISyntaxException& rhs) : IOException(rhs) {
            input = rhs.input;
            index = rhs.index;
        }
        URISyntaxException& operator=(const URISyntaxException &rhs) {
            if (this != &rhs) {
                IOException::operator=(rhs);
                input = rhs.input;
                index = rhs.index;
            }
            return *this;
        }
        URISyntaxException(std::string i, std::string r, int in) : IOException(r) {
            if ((i.length() == 0) || (r.length() == 0)) throw NullPointerException();
            if (in< -1) throw IllegalArgumentException();
            input = i;
            index = in;
        }
        URISyntaxException(std::string i, std::string r): URISyntaxException(i, r, -1) { }
        std::string getInput() { return input; }
        std::string getReason() {
            std::string reason(IOException::what());
            return reason;
        }
        int getIndex() { return index; }
        const char *what() const throw () {
            stringstream ss;
            ss << IOException::what();
            if (index > -1) {
                ss << " at index ";
                ss << index;
            }
            ss << ": ";
            ss << input;
            return ss.str().c_str();
        }
        int describe(char *apStr, int len) {
            std::string str = what();
            if ((apStr) && len > 1)
                return snprintf(apStr, len - 1, "%s", str.c_str());
            return 0;
        }
};
class MalformedURLException : public std::exception {

    public:
        MalformedURLException(std::string &str) {
            snprintf(m_reason, 511, "%s", str.c_str());
        }
        MalformedURLException(const char *str,...) {
            va_list args;
            va_start(args, str);
            vsnprintf(m_reason, 511, str, args);
            va_end(args);
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
class ArrayIndexOutOfBoundsException : public IOException {
    public:
    ArrayIndexOutOfBoundsException() : IOException() { }
    ArrayIndexOutOfBoundsException(std::string str):IOException(str) { }
    ArrayIndexOutOfBoundsException(const char *str,...) {
        va_list args;
        va_start(args, str);
        vsnprintf(m_reason, 511, str, args);
        va_end(args);
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
class MalformedCookieException : public IOException {
    public:
    MalformedCookieException() : IOException() { }
    MalformedCookieException(std::string &s):IOException(s) { }
    MalformedCookieException(const char *str, ...) {
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
class ClientProtocolException : public IOException {
    public:
        ClientProtocolException() : IOException() { }
        ClientProtocolException(std::string s): IOException(s) { }
        ClientProtocolException(const char *str, ...) {
            va_list args;
            va_start(args, str);
            vsnprintf(m_reason, 511, str, args);
            va_end(args);
        }
        ClientProtocolException(const char *str, va_list args) : IOException() {
            vsnprintf(m_reason, 511, str, args);
        }
};
class HttpResponseException  : public ClientProtocolException {
    int statusCode;
    va_list m_args;
    public:
        HttpResponseException(int s, std::string str):ClientProtocolException(str), statusCode(s) {
        }
        HttpResponseException(int s, const char *str, ...): ClientProtocolException(str,  (va_start(m_args, str), m_args)), statusCode(s) {
            va_end(m_args);
        }
        int getStatusCode() { return statusCode; }
};
#endif
