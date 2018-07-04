#include "HttpException.h"
#ifndef SCHEMEREGISTRY_H
#define SCHEMEREGISTRY_H
class SchemeRegistry {
    private:
        std::unordered_map<std::string, Scheme*> registeredSchemes;
    public:
        SchemeRegistry();
        Scheme* getScheme(std::string name);
        Scheme* getScheme(HttpHost *host);
        Scheme* get(std::string name);
        Scheme* registerScheme(Scheme *sch);
        Scheme* unregister(std::string name);
        void getSchemeNames(std::vector<Scheme *> &schs);
        void setItems(std::unordered_map<std::string, Scheme*> &map);
};
#endif
