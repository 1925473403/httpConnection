#include "HttpException.h"
#ifndef URL_H
#define URL_H

class Parts {
    private:
        std::string _query;
        std::string _path;
        std::string _ref;
    public:
        Parts(std::string f) {
            int ind = f.find("#");
        }
        std::string getPath() { return _path; }
        std::string getQuery() { return _query; }
        std::string getRef() { return ref; }
};
class URL {
    private:
        std::string _protocol;
        std::string _host;
        int _port;
        std::string _file;
        std::string _query;
        std::string _authority;
        std::string _userInfo;
        std::string _ref;
        InetAddress hotAddress;
        bool isValidProtocol(std::string pro);
        unordered_map<std::string, URLStreamHandler*> handlers;
    public:
        URL(std::string pro, std::string h, int p, std::string f) throw (MalformedURLException);
        URL(std::string pro, std::string h, std::string f) throw (MalformedURLException);
        URL(std::string pro, std::string h, int p, std::string f, URLStreamHandler *handler) throw (MalformedURLException);
        URL(std::string spec) throw (MalformedURLException);
        URL(URL &context, std::string spec) throw (MalformedURLException);
        URL(URL &content, std::string spec, URLStreamHandler *handler) throw (MalformedURLException);
        void set(std::string pro, std::string h, int p, std::string f, std::string r);
        void set(std::string pro, std::string h, int p, std::string auth, std::string ui, std::string pt, std::string q, std::string rr);
        std::string getQuery();
        std::string getPath();
        std::string getUserInfo();
        std::string getAuthority();
        int getPort();
        int getDefaultPort();
        std::string getHost();
        std::string getFile();
        std::string getRef();
        std::string toString();
        std::string toExternalForm();
	URI toURI() throw (URISyntaxException);
        static URLStreamHandler* getURLStreamHandler(std::string p);
};
#endif
