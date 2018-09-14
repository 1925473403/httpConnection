#include "HttpException.h"
#ifndef NAMERESOLVER_H
#define NAMERESOLVER_H
class NameResolver {
    NameResolver() ;
    NameResolver(const NameResolver &rhs) ;
    NameResolver& operator=(const NameResolver &rhs) ;
    ~NameResolver() ;
    public:
    static void resolve(std::string &str, vector<std::string> &v);
    static void resolve(const char *str, vector<std::string> &v);
};
#endif
