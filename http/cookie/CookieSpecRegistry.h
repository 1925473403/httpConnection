#include "HttpException.h"
#ifndef COOKIESPECREGISTRY_H
#define COOKIESPECREGISTRY_H
class CookieSpecRegistry {
    std::unordered_map<std::string, CookieSpecFactory*> registeredSpecs;
    public:
        CookieSpecRegistry();
        void registerCookieSpec(std::string &name, CookieSpecFactory *factory);
        void unregister(std::string &id);
        CookieSpec* getCookieSpec(std::string &name, HttpParams *params) throw (IllegalStateException);
        CookieSpec* getCookieSpec(std::string &name) throw (IllegalStateException);
        void getSpecNames(vector<std::string> &res);
        void setItems(unordered_map<std::string, CookieSpecFactory *> &m);
};
#endif
