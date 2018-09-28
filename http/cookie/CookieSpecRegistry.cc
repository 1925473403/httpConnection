#include "HttpException.h"
#include "StringUtils.h"
#include "Cookie.h"
#include "CookieSpec.h"
#include "CharArrayBuffer.h"
#include "ProtocolVersion.h"
#include "Header.h"
#include "HeaderIterator.h"
#include "HttpParams.h"
#include "AbstractHttpParams.h"
#include "CookieSpecFactory.h"
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
    auto it = registeredSpecs.find(id);
    if (it != registeredSpecs.end()) {
        CookieSpecFactory *csf = it->second;
        csf->unref();
        registeredSpecs.erase(it);
    }
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
    if (m.size() == 0) return;
    for (auto it = registeredSpecs.begin(); it != registeredSpecs.end(); it++) {
        CookieSpecFactory *cf = it->second;
        if (cf) cf->unref();
    }
    registeredSpecs.clear();
    registeredSpecs.swap(m);
}
