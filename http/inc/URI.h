#include "HttpException.h"
#include "Comparable.h"
#ifndef URI_H
#define URI_H
class URI : Comparable<URI> {
    private:
        std::string scheme;
        std::string fragment;
        std::string authority;
        std::string userInfo;
        std::string host;
        int port ;
        std::string path;
        std::string query;
        std::string schemeSpecificPart;
        int hash;
        std::string decodedUserInfo;
        std::string decodedAuthority;
        std::string decodedPath;
        std::string decodedQuery;
        std::string decodedFragment;
        std::string decodedSchemeSpecificPart;
        std::string string;
        URI() { }
    public:
        URI(const URI &rhs);
        URI& operator=(const URI &rhs);
        URI(std::string str) throw (URISyntaxException);
        URI(std::string scheme, std::string userInfo, std::string host, int port, std::string path, std::string query, std::string fragment) throw (URISyntaxException);
        URI(std::string scheme, std::string authority, std::string path, std::string query, std::string fragment) throw (URISyntaxException);
        URI(std::string scheme, std::string host, std::string path,, std::string fragment) throw (URISyntaxException);
        URI(std::string scheme, std::string ssp, std::string fragment) throw (URISyntaxException);
        static URI create(std::string str);
        URI parseServerAuthority() throw (URISyntaxException);

};
#endif
