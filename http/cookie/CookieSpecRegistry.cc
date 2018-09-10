#include "HttpException.h"
#include "HttpParams.h"
#ifndef COOKIESPECREGISTRY_H
#include "CookieSpecRegistry.h"
#endif
CookieSpecRegistry::CookieSpecRegistry() {
}
void CookieSpecRegistry::registerCookieSpec(std::string &name, CookieSpecFactory *factory) {
    if (name.size() == 0) throw IllegalArgumentException("Name may not be null");
    toLowerCase(name);
    if (factory == nullptr) throw IllegalArgumentException("Cookie spec factory may not be null");
    registeredSpecs.insert(make_pair(name, factory));
}
void CookieSpecRegistry::unregister(std::string &id) {
    if (id.size() == 0) throw IllegalArgumentException("Id may not be null");
    toLowerCase(id);
    registeredSpecs.remove(id);
}
CookieSpec* CookieSpecRegistry::getCookieSpec(std::string &name, HttpParams *params) throw (IllegalStateException) {
    if (name.size() == 0) throw IllegalArgumentException("Name may not be null");
    toLowerCase(name);
    CookieSpecFactory *cf = registeredSpecs[name];
    if (cf != nullptr) {
        return cf->newInstance(params);
    }
    throw IllegalStateException("Unsupported cookie spec: %s", name.c_str());
}
CookieSpec* CookieSpecRegistry::getCookieSpec(std::string &name) throw (IllegalStateException) {
    return getCookieSpec(name, nullptr);
}
void CookieSpecRegistry::getSpecNames(vector<std::string> &res) {
    for (auto it = registeredSpecs.begin(); it != registeredSpecs.end(); it++) res.push_back(it->first);
}
void CookieSpecRegistry::setItems(unordered_map<std::string, CookieSpecFactory *> &m) {
    if (m.size() == ) return;
    for (auto it = registeredSpecs.begin(); it != registeredSpecs.end(); it++) {
        CookieSpecFactory *cf = it->second;
        if (cf) delete cf;
    }
    registeredSpecs.clear();
    registeredSpecs.swap(m);
}
