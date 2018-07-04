#include "HttpException.h"
#include "HttpHost.h"
#include "Scheme.h"
#include <mutex>
#include <thread>
#ifndef SCHEMEREGISTRY_H
#include "SchemeRegistry.h"
#endif
std::recursive_mutex SchemeRegistryMutex;
SchemeRegistry::SchemeRegistry() { }
Scheme* SchemeRegistry::getScheme(std::string name) {
    Scheme *found = get(name);
    if (found == NULL) throw IllegalStateException("Scheme %s not registered.", name.c_str());
    return found;
}
Scheme* SchemeRegistry::getScheme(HttpHost *host) {
    std::unique_lock<std::recursive_mutex> lk(SchemeRegistryMutex);
    if (host == NULL) throw IllegalArgumentException("Host must not be null.");
    return getScheme(host->getSchemeName());
}
Scheme* SchemeRegistry::get(std::string name) {
    std::unique_lock<std::recursive_mutex> lk(SchemeRegistryMutex);
    if (name == "") throw IllegalArgumentException("Name must not be null.");
    std::unordered_map<std::string, Scheme*>::iterator it = registeredSchemes.find(name);
    if (it == registeredSchemes.end()) return NULL;
    return it->second;
}
Scheme* SchemeRegistry::registerScheme(Scheme *sch) {
    std::unique_lock<std::recursive_mutex> lk(SchemeRegistryMutex);
    if (sch == NULL) throw IllegalArgumentException("Scheme must not be null.");
    std::pair<std::unordered_map<std::string, Scheme*>::iterator, bool> insert = registeredSchemes.insert(std::make_pair(sch->getName(), sch));
    if (insert.second == true) return sch;
    return sch;
}
Scheme* SchemeRegistry::unregister(std::string name) {
    std::unique_lock<std::recursive_mutex> lk(SchemeRegistryMutex);
    if (name == "") throw IllegalArgumentException("Name must not be null.");
    std::unordered_map<std::string, Scheme*>::iterator it = registeredSchemes.find(name);
    Scheme *sch = NULL;
    if (it != registeredSchemes.end()) {
        sch = it->second;
        registeredSchemes.erase(it);
    }
    return sch;
}
void SchemeRegistry::getSchemeNames(std::vector<Scheme *> &schs) {
    std::unique_lock<std::recursive_mutex> lk(SchemeRegistryMutex);
    for (std::unordered_map<std::string, Scheme*>::iterator it = registeredSchemes.begin(); it != registeredSchemes.end(); it++) schs.push_back(it->getName());
}
void SchemeRegistry::setItems(std::unordered_map<std::string, Scheme*> &map) {
    std::unique_lock<std::recursive_mutex> lk(SchemeRegistryMutex);
    if (map.size() == 0) return;
    for (std::unordered_map<std::string, Scheme*>::iterator it = registeredSchemes.begin(); it != registeredSchemes.end(); it++) delete it->second;
    registeredSchemes.clear();
    for (std::unordered_map<std::string, Scheme*>::iterator it = map.begin(); it != map.end(); it++) registerScheme(it->second);
}
