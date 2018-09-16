#include "HttpException.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#ifndef NAMERESOLVER_H
#include "NameResolver.h"
#endif
void resolve(std::string &str, vector<std::string> &v) {
    NameResolver::resolve(str.c_str(), v);
}
void NameResolver::resolve(const char *str, vector<std::string> &v) {
    if (str == NULL) return;
    struct hostent *h = gethostbyname(str);
    if (h) {
        for (int i = 0; (i < h->h_length && h->h_addr_list[i]); i++) {
            char *s = h->h_addr_list[i];
            stringstream ss;
            ss << (int)(s[0] &0xff) << "." << ((int)(s[1]&0xff)) << "." << ((int)(s[2]&0xff)) << "." << ((int)(s[3]&0xff));
            std::cout << ss.str() << " ";
            v.push_back(ss.str());
        }
        std::cout << std::endl;
    }
    return;
}

void NameResolver::getnameinfo(const char *ip, vector<std::string> &v) {

    struct sockaddr_in sa;    /* input */
    char hbuf[NI_MAXHOST] = { 0 };

    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(ip);
    if (::getnameinfo((struct sockaddr *)&sa, sizeof(sa), hbuf, sizeof(hbuf), NULL, 0, NI_NAMEREQD)) v.push_back(ip);
    else v.push_back(hbuf);
    return;
}
