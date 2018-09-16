#include "HttpException.h"
#include "HttpParams.h"
#include "AbstractHttpParams.h"
#include "Value.h"
#include <unordered_map>
#ifndef BASICHTTPPARAMS_H
#include "BasicHttpParams.h"
#endif
BasicHttpParams::BasicHttpParams() {
}

ValueBase *BasicHttpParams::getParameter(std::string name) {
    ValueBase* param = 0;
    if (parameters.size() > 0) {
        unordered_map<std::string, ValueBase*>::iterator it = parameters.find(name);
        if (it != parameters.end()) param = it->second;
    }
    return param;
}

HttpParams* BasicHttpParams::setParameter(std::string name, ValueBase *value) {
    if (value) value->ref();
    parameters.insert(std::make_pair(name, value));
    return this;
}

BasicHttpParams::~BasicHttpParams() {
    for (auto it = parameters.begin(); it!= parameters.end(); it++) {
        ValueBase *v = it->second;
        if (v != NULL) v->unref();
    }
    parameters.clear();
}

void BasicHttpParams::setParameters(vector<std::string> &names, ValueBase *value) {
    for (size_t i = 0; i < names.size(); i++) {
        if (value) value->ref();
        setParameter(names[i], value);
    }
}

bool BasicHttpParams::removeParameter(std::string name)  {
    if (parameters.size() == 0) return false;
    unordered_map<std::string, ValueBase*>::iterator it = parameters.find(name);
    if (it != parameters.end()) {
        ValueBase *v = it->second;
        v->unref();
        parameters.erase(it);
        return true;
    }
    return false;
}

bool BasicHttpParams::isParameterSet(std::string name) {
    return getParameter(name) != 0;
}

bool BasicHttpParams::isParameterSetLocally(std::string name) {
    return (parameters.size() != 0 && (parameters.find(name) != parameters.end()));
}

void BasicHttpParams::copyParams(HttpParams *target) {
}
