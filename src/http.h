#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

/* OpenSSL headers */
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iterator>

#include "STokenizer.h"
#include "url.h"

using namespace std;

typedef std::basic_string<unsigned char> ustring;

class HttpResponse;
class hexdump {
    hexdump() { }
    hexdump(const hexdump& rhs);
    void operator=(const hexdump &rhs);
    public:
        static hexdump& getinstance() { 
            static hexdump od;
            return od;
        }
        void dump(unsigned char *pBuf, size_t len) {
            for (int j = 0; j < len; j+= 16) {
                for (int i = 0; i < 16; i++) {
                    printf("%02x ", pBuf[i + j]);
                }/*
                for (int i = 0; i < 16; i++) {
                    printf("%c", pBuf[j+i]);
                }*/
                printf("\n");
            }
        }
        void dump(ofstream &ofs, unsigned char *pBuf, size_t len) {
            //ofs.write("###########################################\n", strlen("###########################################\n"));
            for (int j = 0; j < len; j+= 16) {
                char str[512] = { 0 };
                for (int i = 0; i < 16; i++) {
                    sprintf(str + strlen(str), "%02x ", pBuf[i + j]);
                }
                sprintf(str + strlen(str), "\n");
                ofs.write(str, strlen(str));
            }
        }
};

#ifndef HTTP_H
#define HTTP_H
class HTTPHeader {
    std::unordered_map<std::string, std::string> m_header;
    private:
    void copy(const HTTPHeader& rhs) {
        std::unordered_map<std::string, std::string>& rhsMap = *(rhs.getheader());
        for (std::unordered_map<std::string, std::string>::iterator it = rhsMap.begin(); it != rhsMap.end(); it++) {
            m_header.insert(std::make_pair(it->first, it->second));
        }
    }
    public:
    HTTPHeader(const char *str) { 
        if (memcmp(str, "HTTP", 4) == 0) {
            m_header.insert(std::make_pair("", string(str)));
        } else {
            STokenizer<string, char> s((char *)str, strlen(str), ":");
            std::string key = s.getnext();
            std::string val = s.getall();
            m_header.insert(std::make_pair(key, val));
        }
    }
    HTTPHeader(const HTTPHeader &rhs) { 
        copy(rhs);
    }
    HTTPHeader& operator=(const HTTPHeader& rhs) {
        if (this == &rhs) return *this;
        copy(rhs);
        return *this;
    }
    string equals(const char *s) {
        for (std::unordered_map<std::string, std::string>::iterator it = m_header.begin(); it != m_header.end(); it++)
            if (it->first.find(s) != string::npos) return it->second;
        return "";
    }
    std::unordered_map<std::string, std::string>* getheader() const { return (std::unordered_map<std::string, std::string> *)&m_header; }
    string toString() {
        stringstream ss;
        for (std::unordered_map<std::string, std::string>::iterator it = m_header.begin(); it != m_header.end(); it++)
            ss << it->first << ":" << it->second << "\n";
        return ss.str();
    }
};

ostream& operator<<(ostream &os, HTTPHeader &rhs) {
    os << rhs.toString() ;
    return os;
}
char hex_chars[256];

static void init_hex() {
    hex_chars[0x30] = 0;
    hex_chars[0x31] = 1;
    hex_chars[0x32] = 2;
    hex_chars[0x33] = 3;
    hex_chars[0x34] = 4;
    hex_chars[0x35] = 5;
    hex_chars[0x36] = 6;
    hex_chars[0x37] = 7;
    hex_chars[0x38] = 8;
    hex_chars[0x39] = 9;
    hex_chars['a'] = 0xa;
    hex_chars['b'] = 0xb;
    hex_chars['c'] = 0xc;
    hex_chars['d'] = 0xd;
    hex_chars['e'] = 0xe;
    hex_chars['f'] = 0xf;
    hex_chars['A'] = 0xa;
    hex_chars['B'] = 0xb;
    hex_chars['C'] = 0xc;
    hex_chars['D'] = 0xd;
    hex_chars['E'] = 0xe;
    hex_chars['F'] = 0xf;
}

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}
class HttpResponse {
   int extractHeaders(unsigned char *buf, size_t len) {
        STokenizer<ustring, unsigned char> st(buf, len);
        while (st.hasnext()) {
            ustring l = st.getnext();
            if (l.size() == 0) break;
            string s;
            s.assign((const char *)l.data(), l.length());
            HTTPHeader hdr = HTTPHeader(s.c_str());
            headers.push_back(hdr);
            if (s.find("Transfer-Encoding") != string::npos) {
                string val = hdr.equals("Transfer-Encoding");
                isChuncked = (val == " chunked")? true:false;
            } else if (s.find("Content-Length") != string::npos) {
                string val = hdr.equals("Content-Length");
                contentLength = strtoul(val.c_str(), 0, 0);
            }
        }
        st.getnext();
        return st.getsize() ;
    }
    vector<HTTPHeader> headers;
    bool isChuncked;
    long chunklength;
    size_t contentLength;
    ustring _payload;
    string _responseCode;
    public:
    HttpResponse() : contentLength(0), isChuncked(false) , chunklength(0) { }
    HttpResponse(unsigned char *buf, size_t len) :contentLength(0), isChuncked(false), chunklength(0) {
        size_t l = extractHeaders(buf, len);
        _payload.append(buf + l, len - l);
    }
    ~HttpResponse() { }
    string  getResponseCode() { return _responseCode; }
    const unsigned char* payload_data() const { return _payload.data(); }
    ustring payload() { return _payload; }
    void append(unsigned char *buf, size_t len) {
        int l = 0;
        //fprintf(stderr, "1. chunklength: %ld, len: %ld, l = %d\n", chunklength, len, l);
        //if (len > 0) {
        //    ofstream ofs ("DEBUG.txt", std::ofstream::binary|std::ofstream::app);
        //    hexdump::getinstance().dump(ofs, buf, len);
        //    ofs.close();
        //}
        if (memcmp(buf, "HTTP", 4) == 0) {
            _responseCode.assign((char *)(buf + strlen("HTTP/1.1 ")), 3);
            l = extractHeaders(buf, len);
            dump_headers();
        }
        len -= l;
        //fprintf(stderr, "2. chunklength: %ld, len: %ld, l = %d\n", chunklength, len, l);
        if (isChuncked) {
            if (isChuncked && chunklength > 0 && len > 0) {
                size_t minlen = std::min<size_t>(len, (size_t)chunklength);
                //std::ofstream ofs ("Title.mp3", std::ofstream::binary|std::ofstream::app);
                //ofs.write((char *)buf, minlen);
                //ofs.close();
                //fprintf(stderr, "minlen: %ld, chunklength: %ld, len: %ld, l = %d\n", minlen, chunklength, len, l);
                //fprintf(stderr, "[%.*s]\n", minlen, buf + l);
                _payload.append(buf + l, minlen);
                l+= minlen;
                chunklength -= minlen;
                len -= minlen;
            }
            if (isChuncked && len > 0) {
                long chunklen = 0;
                if (buf[l] == '\r' && buf[l+1] == '\n') { l+=2; len -= 2; }
                STokenizer<ustring, unsigned char> st(buf + l, len, "\r\n");
                if (st.hasnext()) {
                    ustring chunklengthstr = st.getnext();
                    //fprintf(stderr, "chunklengthstr: %s\n", chunklengthstr.c_str());
                    for (int i = 0; i < chunklengthstr.length(); i++) chunklen = (chunklen << 4) | hex_chars[chunklengthstr[i]];
                    std::cout << "chunklength: " << chunklen<< std::endl;
                    l += chunklengthstr.length() + 2;
                    len -= (chunklengthstr.length() + 2);
                }
                chunklength += chunklen;
            }
            if (isChuncked && chunklength > 0 && len > 0) {
                size_t minlen = std::min<size_t>(len, (size_t)chunklength);
                //std::ofstream ofs ("Title.mp3", std::ofstream::binary|std::ofstream::app);
                //ofs.write((char *)buf + l, len);
                //ofs.close();
                //fprintf(stderr, "minlen: %ld, chunklength: %ld, len: %ld, l = %d\n", minlen, chunklength, len, l);
                //fprintf(stderr, "[%.*s]\n", minlen, buf + l);
                _payload.append(buf + l, minlen);
                l+= minlen;
                chunklength -= minlen;
                len -= minlen;
            }
        } else {
            //std::ofstream ofs ("Title.mp3", std::ofstream::binary|std::ofstream::app);
            //ofs.write((char *)buf + l, len);
            //ofs.close();
            _payload.append(buf + l, len);
        }
    }
    size_t contentlength() const {
        return contentLength;
    }
    void dump_headers() {
        for (int i = 0; i <headers.size(); i++)
            std::cout << headers[i] ;
    }
    string getHeaderField(const char *name) {
        string val = "";
        for (int i = 0; i < headers.size(); i++) {
            val = headers[i].equals(name);
            if (val.length() > 0) break;
        }
        ltrim(val);
        rtrim(val);
        return val;
    }
};

class HttpConnection {
    protected:
        Url &m_url;
        tcpClient *client;
    public:
    HttpConnection (Url &u) : m_url(u), client(0) {
        init_hex();
    }

    Url& url() { return m_url; }
    virtual void connect() {
        struct host h;
        vector<string> src, dst;
        h.resolve((char *)m_url.host().c_str(), dst);
        if (dst.size() == 0) throw MalformedURLException((const char *)"HttpConnection connect(): unable to get remote host details: " , m_url.host());

        char hostname[256] = { 0 } ;
        if (gethostname(hostname, 256) < 0) throw IOException("HttpConnection connect(): unable to get hostname");

        h.resolve((char *)hostname, src);
        if (src.size() == 0) throw IOException((const char *)"HttpConnection connect(): unable to get localhost details");
        for (int i = 0; i < dst.size(); i++) {
            try {
                client = new tcpClient((char *)src[0].c_str(), 6589);
                if (!client) throw MalformedURLException((const char *)"HttpConnection connect(): unable to bind to localhost: ", src[0]);
                client->connect((char *)dst[i].c_str(), m_url.getport());
                sleep(1); return;
            } catch (const IOException &e) {
                delete client;
                client = 0;
                std::cerr << e.what() << std::endl;
            }
        }
        throw IOException("All connect attempts exhausted");
    }
    virtual ~HttpConnection() { 
        std::cout << "HttpConnection dtor" << std::endl;
        if (client) delete client;
    }
    virtual int net_read(unsigned char *pBuffer, size_t len) {
        return client->net_read(pBuffer, len);
    }
    virtual int net_write(unsigned char *pBuffer, size_t len) {
        return client->net_write(pBuffer, len);
    }
};

class HttpsConnection : public HttpConnection {
    SSL_CTX *ctx;
    SSL *ssl;
    SSL_CTX* InitCTX(void)
    {   SSL_METHOD *method;
        SSL_CTX *ctx;
 
        OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
        SSL_load_error_strings();   /* Bring in and register error messages */
        method = (SSL_METHOD *)TLSv1_2_client_method();  /* Create new client-method instance */
        ctx = SSL_CTX_new(method);   /* Create new context */
        if ( ctx == NULL ) {
            ERR_print_errors_fp(stderr);
            abort();
        }
        return ctx;
    }
    void ShowCerts(SSL* ssl) {
        X509 *cert;
        char *line;
 
        cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
        if ( cert != NULL ) {
            printf("Server certificates:\n");
            line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
            printf("Subject: %s\n", line);
            free(line);       /* free the malloc'ed string */
            line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
            printf("Issuer: %s\n", line);
            free(line);       /* free the malloc'ed string */
            X509_free(cert);     /* free the malloc'ed certificate copy */
        } else printf("Info: No client certificates configured.\n");
    }

    std::string getErrorStrings(const char *fn) {
    std::string ret(fn);
    ret += " SSL Error queue: ";
    if (ERR_peek_error() == 0) {
        ret += " Empty";
        return ret;
    }
    for (int errCode=ERR_get_error(); errCode!=0; errCode=ERR_get_error()) {
            char buf[512];
        std::string p(ERR_error_string(errCode, buf));
        ret += " [" + p + "]";
    }
    return ret;
    }
    public:
    HttpsConnection(Url &u) : 
        HttpConnection(u),
        ctx(0),
        ssl(0) {
            SSL_library_init();
            ctx = InitCTX();
    }
    ~HttpsConnection() {
        std::cout << "HttpsConnection dtor" << std::endl;
        if (ssl) {
            int rc=SSL_shutdown(ssl);
            if (!rc) {
                rc = SSL_shutdown(ssl);
            }
//            int err = errno;
//            if (!rc) { std::cout << "SSL_shutdown()" << std::endl; rc = SSL_shutdown(ssl); }
//            if (rc != 1)
//                std::cerr << getErrorStrings("SSL_shutdown()") << " system error: (" << err << " : " << strerror(err) << ")" << std::endl;
            SSL_free(ssl);
        }
        if (ctx) SSL_CTX_free(ctx);
    }
    void connect() {
        HttpConnection::connect();
        /* create new SSL connection state */
        ssl =  SSL_new(ctx);

        /* attach the socket descriptor */
        int server = client->getfd();
        SSL_set_fd(ssl, server);

        int ret = SSL_connect(ssl);
        if ( ret <= 0 ) {
            int error = SSL_get_error (ssl, ret);
            switch (error) {
                case SSL_ERROR_WANT_READ:
                    /*  A read operation failed.  Call SSL_read again with
                     * the same arguments once bytes are available on
                     * the socket. */
                    throw IOException("SSL_ERROR_WANT_READ\n");
                    break;
                case SSL_ERROR_WANT_WRITE:
                    /* A write operation failed.  When the socket is
                     * available for writing, call the SSL function again.
                     * Generally, SSL_read won't cause this value to be
                     * thrown, but it is a good idea to check for and deal
                     * with it if it comes up. */
                    throw IOException("SSL_ERROR_WANT_WRITE\n");
                    break;
                case SSL_ERROR_WANT_CONNECT:
                    /* If a connect BIO was used, then this will indicate
                     * that the socket is not yet connected.  Wait until the
                     * socket is connected before re-calling SSL_read. */
                    throw IOException("SSL_ERROR_WANT_CONNECT\n");
                    break;
                case SSL_ERROR_WANT_X509_LOOKUP:
                    /* This indicates that the SSL-C library is waiting for the
                     * lookup of a digital certificate to complete.  Re-call the
                     * SSL_read function again when this operation has
                     * completed. */
                    throw IOException("SSL_ERROR_WANT_X509_LOOKUP\n");
                    break;
           }
        } else {
            printf("\n\nConnected with %s encryption\n", SSL_get_cipher(ssl));
            ShowCerts(ssl);        /* get any certs */

//            string msg = "GET /";
//            msg += m_url.path() ;
//            msg += " HTTP/1.1\r\n";
//            msg.append("Host: ");
//            msg.append(m_url.host());
//            msg.append("\r\nAccept: */*\r\n\r\n");
//            SSL_write(ssl, msg.c_str(), msg.length());
//            HttpResponse httpRes;
//            unsigned char pBuf[1<<15];
//            for (;;) {
//                memset(pBuf, 0, (1<<15));
//                int packetlen = SSL_read(ssl, pBuf, (1<<15));
//                if (packetlen > 0) {
//                    pBuf[packetlen] = 0;
//                    httpRes.append(pBuf, packetlen);
//                    hexdump::getinstance().dump(pBuf, packetlen);
//                    if (strcasestr((char *)pBuf, "</html>") != NULL) break;
//                } else if (packetlen == 0) break;
//            }

        }
    }
    int net_read(unsigned char *pBuf, size_t len) {
        if (ssl) {
            return SSL_read(ssl, pBuf, len);
        }
        return 0;
    }
    int net_write(unsigned char *pBuf, size_t len) {
        if (ssl) {
            return SSL_write(ssl, pBuf, len);
        }
        return 0;
    }
};

class HttpConnectionFactory {
    Url &m_url;
    public:
    HttpConnectionFactory(Url &u):m_url(u) {
    }

    HttpConnection* getHttpConnection() {
        if (m_url.protocol() == "http") return new HttpConnection(m_url);
        else if (m_url.protocol() == "https") return new HttpsConnection(m_url);
        return 0;
    }
};
#endif
