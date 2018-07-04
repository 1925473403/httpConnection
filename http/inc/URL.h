#include "HttpException.h"
#ifndef URL_H
#define URL_H

class Parts {
    private:
        std::string _query;
        std::string _path;
        std::string _ref;
    public:
        Parts(std::string f);
        Parts(const Parts &rhs);
        Parts& operator=(const Parts &rhs) ;
        std::string getPath() { return _path; }
        std::string getQuery() { return _query; }
        std::string getRef() { return _ref; }
};
class URLStreamHandler;
class URLStreamHandlerFactory;
class URL {
    private:
        std::string protocol;
        std::string host;
        std::string path;
        int port;
        std::string file;
        std::string query;
        std::string authority;
        std::string userInfo;
        std::string ref;
        static URLStreamHandlerFactory *urlStreamHandlerFactory;
        bool isValidProtocol(std::string pro);
        static unordered_map<std::string, URLStreamHandler*> handlers;
    public:
        InetAddress *hostAddress;
        URLStreamHandler *handler;
        URL(const URL &rhs);
        URL& operator=(const URL &rhs);
        URL(std::string &spec) throw (MalformedURLException);
        URL(std::string pro, std::string h, int p, std::string f) throw (MalformedURLException);
        URL(std::string pro, std::string h, std::string f) throw (MalformedURLException);
        URL(std::string pro, std::string h, int p, std::string f, URLStreamHandler *hand) throw (MalformedURLException);
        URL(URL &context, std::string &spec) throw (MalformedURLException);
        URL(URL &content, std::string &spec, URLStreamHandler *handler) throw (MalformedURLException);
        ~URL();
        void set(std::string pro, std::string h, int p, std::string f, std::string r);
        void set(std::string pro, std::string h, int p, std::string auth, std::string ui, std::string pt, std::string q, std::string rr);
        std::string getQuery();
        std::string getPath();
        bool sameFile(URL &other);
        std::string getUserInfo();
        std::string getAuthority();
        int getPort();
        int getDefaultPort();
        std::string getHost();
        std::string getFile();
        std::string getRef();
        std::string toString();
        std::string getProtocol();
        std::string toExternalForm();
        URI toURI() throw (URISyntaxException);
        static URLStreamHandler* getURLStreamHandler(std::string p);
};
#endif
