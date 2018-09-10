#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/socket.h> /* socklen_t, etc */
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <fstream>
#include <iterator>
#include <list>
#include <sstream>
#include "HttpDateGenerator.h"

/* regex */
#include <sys/types.h>
#include <regex.h>

/* OpenSSL headers */
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"


#include "utils.h"
#include "transport.h"
#include "STokenizer.h"
#include "url.h"
#include "http.h"

using namespace std;
#define READSZ (1<<15)
HttpDateGenerator DEFAULTDATEGENERATOR;
SSL_CTX* InitCTX(void)
{   SSL_METHOD *method;
    SSL_CTX *ctx;
 
    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */
    method = (SSL_METHOD *)TLSv1_2_client_method();  /* Create new client-method instance */
    ctx = SSL_CTX_new(method);   /* Create new context */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}
  
void ShowCerts(SSL* ssl)
{   X509 *cert;
    char *line;
 
    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if ( cert != NULL )
    {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);       /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);       /* free the malloc'ed string */
        X509_free(cert);     /* free the malloc'ed certificate copy */
    }
    else
        printf("Info: No client certificates configured.\n");
}

void replace(std::string &s, const char *what, const char *with) {
    for (int pos = s.find(what); pos != string::npos; pos = s.find(what, ++pos)) {
        s.replace(pos, strlen(what), with);
    }
}

string getIndex() {
    string val = "";
    ifstream ifs("index.dat", ifstream::in);
    if (!ifs.is_open()) return val;
    while (!ifs.eof()) ifs >> val;
    ifs.close();
    return val;
}

void spawn_client_thread(int fd, struct sockaddr_in *addr, socklen_t *addrlen) {
    std::cout << "New connection from " << inet_ntoa(addr->sin_addr) << std::endl;
    tcpClient tClient(fd);
/*
 * HTTP/1.1 301 Moved Permanently
 * Date: Sat, 08 Sep 2018 16:45:33 GMT
 * Content-Type: text/html; charset=iso-8859-1
 * Transfer-Encoding: chunked
 * Connection: keep-alive
 * Set-Cookie: __cfduid=d4ace31a2ce982d46e03a5fda6f3f54451536425133; expires=Sun, 08-Sep-19 16:45:33 GMT; path=/; domain=.downloadming.ms; HttpOnly
 * Location: https://downloadming.live/haadsaa-1983-mp3-songs
 * CF-Cache-Status: HIT
 * Cache-Control: private, max-age=86400
 * Server: cloudflare
 * CF-RAY: 4572e2dda7975a32-BOS
 * chunklength: 256
 */

/*
 * HTTP/1.1 200 OK
 * Date: Sat, 08 Sep 2018 17:07:19 GMT
 * Content-Type: text/html; charset=UTF-8
 * Transfer-Encoding: chunked
 * Connection: keep-alive
 * Set-Cookie: __cfduid=df36614a128888c6b464b1598c6fee56d1536426439; expires=Sun, 08-Sep-19 17:07:19 GMT; path=/; domain=.downloadming.live; HttpOnly
 * Vary: Accept-Encoding,Cookie
 * Cache-Control: public, max-age=31536000
 * CF-Cache-Status: HIT
 * Expires: Sun, 08 Sep 2019 17:07:19 GMT
 * Expect-CT: max-age=604800, report-uri="https://report-uri.cloudflare.com/cdn-cgi/beacon/expect-ct"
 * Server: cloudflare
 * CF-RAY: 457302bfebc0472e-EWR
 *
 */

// GET / HTTP/1.1
// Host: 192.168.1.84:64001
// User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:31.0) Gecko/20100101 Firefox/31.0
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
// Accept-Language: en-US,en;q=0.5
// Accept-Encoding: gzip, deflate
// Connection: keep-alive

  
    const int flags = fcntl(fd, F_GETFL, 0);
    std::cout << DEFAULTDATEGENERATOR.getCurrentDate() << std::endl;
    if (flags & O_NONBLOCK) std::cout << "set_blocking_mode(): socket was already in non-blocking mode" << std::endl;
    fcntl(fd, F_SETFL, flags ^ O_NONBLOCK);
    std::string name("");
    HttpRequest httpReq;
    while (usleep(800)==0) {
        unsigned char buf[1024] = { 0 };
        int len = tClient.net_read(buf, 1024);
        if (len > 0) {
            httpReq.append(buf, len);
            if (httpReq.method() == "GET") {
                stringstream ss ;
                ss << "HTTP/1.1 200 OK\r\n";
                ss << "Date: " << DEFAULTDATEGENERATOR.getCurrentDate() <<"\r\n";
                ss << "Content-Type: text/html; charset=UTF-8\r\n";
                ss << "Connection: keep-alive\r\n";
                ss << "Server: rhel71\r\n";
                ss << "\r\n";
                ss << "<html><head>GET</head><body><h4>Hello [" << name << "]</h4>";
                ss << "<form method=\"post\" action=\"\"><textarea name=\"history\" cols=\"150\" rows=\"20\">Enter install history here...</textarea> <br/>";
                ss << "<button type=\"submit\" class=\"btn btn-success\">Submit</button>";
                ss << "</form>";
                ss << "</body></html>";
                tClient.net_write((unsigned char *)ss.str().c_str(), (size_t )ss.str().length());
                break;
            } else if (httpReq.method() == "POST") {
                stringstream ss ;
                ss << "HTTP/1.1 200 OK\r\n";
                ss << "Date: " << DEFAULTDATEGENERATOR.getCurrentDate() <<"\r\n";
                ss << "Content-Type: text/html; charset=UTF-8\r\n";
                ss << "Connection: keep-alive\r\n";
                ss << "Server: rhel71\r\n";
                ss << "\r\n";
                ss << "<html><head>POST</head><body><h4>Hello [" << name << "]</h4>";
                ss << "<form method=\"post\" action=\"\"><textarea name=\"history\" cols=\"150\" rows=\"20\">Enter install history here...</textarea> <br/>";
                ss << "<button type=\"submit\" class=\"btn btn-success\">Submit</button>";
                ss << "</form>";
                ss << "</body></html>";
                tClient.net_write((unsigned char *)ss.str().c_str(), (size_t )ss.str().length());
                break;
            }
        }
    }
    ::close(fd);
}

class MyServer : public tcpServer {
    public:
    MyServer(std::string &name, int port) : tcpServer(name.c_str(), port) { }
    void incomingCall(int fd, struct sockaddr_in *addr, socklen_t *addrlen) {
        spawn_client_thread(fd, addr, addrlen);
    }
    ~MyServer() {
    }
};


void* server_thread(void *args) {
    std::string src; int port;
    std::cout << "enter server host name and port: " ;
    cin >> src >> port;
    struct host h;
    vector<std::string> res;
    h.resolve((char *)src.c_str(), res);
    for (std::string s : res) {
        std::cout << "[" << s << "]" << std::endl;
    }

    struct pollfd pfds[2] = { 0 };
    try {
        MyServer server(res[0], port);
        pfds[0].events = 0;
        pfds[0].events |= POLLIN | POLLPRI;
        pfds[0].fd = server.getfd();
        try {
            while(usleep(800) == 0) {
                int rc = poll(pfds, 1, 800);
                for (int count = 0; rc > 0 && count >= 0; count--) {
                    struct pollfd *p = pfds  + count;
                    if (p->revents) {
                        if (p->revents & (POLLIN | POLLPRI)) {
                            struct sockaddr_in client_addr; socklen_t len;
                            int clientfd = accept(server.getfd(), (struct sockaddr *)&client_addr, &len);
                            spawn_client_thread(clientfd, &client_addr, &len);
                        }
                    }
                }
            }
        } catch(const IOException &e) {
        }
    } catch (const IOException &e) {
    }
    return NULL;
}
void Test_Server() {
    pthread_t server_tid;
    if (pthread_create(&server_tid, NULL, server_thread, NULL) < 0) {
        throw IOException("cannot create server thread");
    }
    pthread_join(server_tid, NULL);
}

int main() {
    Test_Server();
    return 0;
    try {
        string indexStr = getIndex();
        std::cout << indexStr << std::endl;
        int n ; cin >> n;
        std::string method, str; cin >> str;
        Url u(str);
        cin >> str;
        cin >> method;
        unsigned char pBuf[READSZ] = { 0 };
        HttpConnectionFactory *h = new HttpConnectionFactory(u);

        HttpConnection *client = h->getHttpConnection();
        client->connect();
        
        for (int i = 0; i < n - 1; i++) {
            string tempStr="";
            if (indexStr.length() > 0) {
                while (tempStr.find(indexStr) == string::npos) 
                    cin >> tempStr;
            }
            indexStr = "";
            HttpResponse httpRes;
            cin >> tempStr;
            std::cout << "tempStr: " << tempStr << std::endl;
            Url ua(tempStr);
            if ((i % 5) == 0) {
                delete client;
                delete h;
                h = new HttpConnectionFactory(ua);
                client = h->getHttpConnection(); client->connect();
            }
            if (ua.host() == u.host()) u.setpath(ua.path());
            else { 
                std::cout << "Disconnecting " << u.host() << std::endl;
                std::cout << "Connecting " << ua.host() << std::endl;
                delete client;
                delete h;
                h = new HttpConnectionFactory(ua);
                client = h->getHttpConnection();
                client->connect();
            }
            stringstream ss;
            ss << method << " /" << ua.path() << " HTTP/1.1\r\n";
            ss << "Host: " << ua.host() << "\r\n";
            ss << "Accept: */*\r\n";
            ss << "\r\n";
            std::cout << "-------------------------------------" << std::endl;
            std::cout << ss.str() << std::endl;
            client->net_write((unsigned char *)ss.str().c_str(), (size_t )ss.str().length());
            for (;;) {
                memset(pBuf, 0, READSZ);
                int packetlen = client->net_read(pBuf, READSZ);
                if (packetlen > 0) {
                    httpRes.append(pBuf, packetlen);
                    if (httpRes.getResponseCode() == "301") {
                        string tempUrlStr = httpRes.getHeaderField("Location");
                        Url tempUrl(tempUrlStr);
                        stringstream ss;
                        ss << method << " /" << tempUrl.path() << " HTTP/1.1\r\n";
                        ss << "Host: " << ua.host() << "\r\n";
                        ss << "Accept: */*\r\n";
                        ss << "\r\n";
                        std::cout << "-------------------------------------" << std::endl; std::cout << ss.str() << std::endl;
                        client->net_write((unsigned char *)ss.str().c_str(), (size_t )ss.str().length());
                    }
                    //hexdump::getinstance().dump(pBuf, packetlen);
                    if (httpRes.contentlength() == httpRes.payload().length()) break;
                    //else if (strcasestr((char *)pBuf, "</html>") != NULL) break;
                    else if (httpRes.payload().find((unsigned char *)"</html>") != string::npos) break;
                    //printf("\rProgress : %-3d", (httpRes.payload().length()*100)/httpRes.contentlength());
                    //fflush(stdout);
                }
            }

            string path = ua.path();
            replace(path, "%20", " ");
            int pos = path.find_last_of("/");
            if (pos != string::npos) path  = path.substr(pos+1);
            std::cout << "path: " << path << std::endl;
            ofstream findex ("index.dat", std::ofstream::binary|std::ofstream::app);
            findex << path << std::endl;
            findex.close();
            if ((path.find(".mp3") ==  string::npos) &&
                (path.find(".MP3") ==  string::npos))
               path = "Title.htm";
            std::cout << path << std::endl;
            ofstream ofs(path, std::ofstream::binary|std::ofstream::app);
            ofs.write((char *)httpRes.payload().c_str(), httpRes.payload().length());
            ofs.close();
            u = ua;
        }
        delete client;
        delete h;
    } catch (std::exception &e) {
        std::cerr<< e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
    }
 }

 
//int main(int argc, char **argv) {
//
//    SSL_CTX *ctx;
//    int server;
//    SSL *ssl;
//
//    vector<string> src, dst;
//    struct pollfd pfds[2] = { 0 };
//    unsigned char pBuf[READSZ] = { 0 };
//    int packetlen = 0, incoming = 0;
//    init_hex();
//    HTTPResponse httpRes;
//
//    SSL_library_init();
//    ctx = InitCTX();
//
//    try {
//        std::string str, method;
//        cin >> str;
//        Url u(str);
//        struct host h;
//        h.resolve((char *)u.host().c_str(), dst);
//
//        cin >> str;
//        h.resolve((char *)str.c_str(), src);
//
//        cin >> method;
//        stringstream ss;
//        ss << method << " /" << u.path() << " HTTP/1.1\r\n";
//        ss << "Host: " << u.host() << "\r\n";
//        ss << "Accept: */*\r\n";
//        ss << "\r\n";
//        string msg = ss.str();
// 
//        tcpClient t((char *)src[0].c_str(), 6580);
//
//        for (int i = 0; i < dst.size(); i++) {
//            try {
//                t.connect((char *)dst[i].c_str(), u.getport());
//                sleep(1);
//                std::cout << "connected to " << dst[i] << std::endl;
//                break;
//            } catch (const IOException &ex) {
//                std::cerr<< ex.what() << std::endl;
//            }
//        }
//
//        if (u.protocol() == "https") {
//            ssl = SSL_new(ctx);      /* create new SSL connection state */
//            server = t.getfd();
//            SSL_set_fd(ssl, server);    /* attach the socket descriptor */
//            int ret = SSL_connect(ssl);
//            if ( ret <= 0 ) {  /* perform the connection */
//                int error = SSL_get_error (ssl, ret);
//                switch (error) {
//                    case SSL_ERROR_WANT_READ:
//                        /*  A read operation failed.  Call SSL_read again with
//                         * the same arguments once bytes are available on
//                         * the socket. */
//                        ret = SSL_read(ssl, pBuf, READSZ);
//                        printf("SSL_ERROR_WANT_READ\n");
//                        break;
//                    case SSL_ERROR_WANT_WRITE:
//                        /* A write operation failed.  When the socket is
//                         * available for writing, call the SSL function again.
//                         * Generally, SSL_read won't cause this value to be
//                         * thrown, but it is a good idea to check for and deal
//                         * with it if it comes up. */
//                        printf("SSL_ERROR_WANT_WRITE\n");
//                        break;
//                    case SSL_ERROR_WANT_CONNECT:
//                        /* If a connect BIO was used, then this will indicate
//                         * that the socket is not yet connected.  Wait until the
//                         * socket is connected before re-calling SSL_read. */
//                        printf("SSL_ERROR_WANT_CONNECT\n");
//                        break;
//                    case SSL_ERROR_WANT_X509_LOOKUP:
//                        /* This indicates that the SSL-C library is waiting for the
//                         * lookup of a digital certificate to complete.  Re-call the
//                         * SSL_read function again when this operation has
//                         * completed. */
//                        printf("SSL_ERROR_WANT_X509_LOOKUP\n");
//                        break;
//                }
//                ERR_print_errors_fp(stderr);
//            } else {
//                printf("\n\nConnected with %s encryption\n", SSL_get_cipher(ssl));
//                ShowCerts(ssl);        /* get any certs */
//                SSL_write(ssl, msg.c_str(), msg.length());
//
//                for(;;) {
//                    memset(pBuf, 0, READSZ);
//                    packetlen = SSL_read(ssl, pBuf, READSZ);
//                    if (packetlen > 0) { 
//                        pBuf[packetlen] = 0;
//                        httpRes.append(pBuf, packetlen);
//                        hexdump::getinstance().dump(pBuf, packetlen);
//                        if (strcasestr((char *)pBuf, "</html>") != NULL) break;
//                    }
//                    else if (packetlen == 0) break;
//                }
//                SSL_free(ssl);        /* release connection state */
//                SSL_CTX_free(ctx);        /* release context */
//            }
//            return 0;
//        } 
//        t.net_write((unsigned char *)msg.c_str(), (size_t )msg.length());
//        std::cout << msg << std::endl;
//        pfds[0].events = 0;
//        pfds[0].events |= POLLIN | POLLPRI;
//        pfds[0].fd = t.getfd();
//        while (!incoming) {
//            int rc = poll(pfds, 1, 1000);
//            for (int count = 0; rc > 0 && count >= 0; count--) {
//                struct pollfd *p = pfds  + count;
//                if (p->revents) {
//                    if (p->revents & (POLLIN | POLLPRI)) {
//                        for (int i = 0; i < 128; i++) {
//                            packetlen = t.net_read(pBuf, READSZ);
//                            if (packetlen > 0) {
//                                httpRes.append(pBuf, packetlen);
//                                hexdump::getinstance().dump(pBuf, packetlen);
//                                if (httpRes.payload().length() >= httpRes.contentlength()) break;
//                                std::cout << httpRes.payload().length()  << "==" << httpRes.contentlength() << std::endl;
//                            }
//                        }
//                    }
//                    if (p->revents & POLLOUT) {
//                        for (int i = 0; i < 128; i++) {
//                            memcpy(pBuf, msg.c_str(), msg.length());
//                            t.net_write(pBuf, msg.length());
//                        }
//                    }
//                }
//            }
//        }
//    } catch (IOException &e) {
//        std::cout << e.what() << std::endl;
//    } catch (std::exception &e) {
//        std::cerr << e.what() << std::endl;
//    } catch (...) {
//        std::cout << "Unknown error" << std::endl;
//    }
//    return 0;
//}

