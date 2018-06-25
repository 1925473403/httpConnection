#include "HttpException.h"
#include "Value.h"
#include "HttpParams.h"
#include "AbstractHttpParams.h"
#ifndef DEFAULTEDHTTPPARAMS_H
#include "DefaultedHttpParams.h"
#endif
DefaultedHttpParams::DefaultedHttpParams(HttpParams* l,  HttpParams* d) :local(l), defaults(d) {
    if (local == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
}

HttpParams* DefaultedHttpParams::copy() {
    return this;
}

ValueBase *DefaultedHttpParams::getParameter(std::string name) {
    ValueBase *v = local->getParameter(name);
    if (v == NULL && defaults != NULL) v = defaults->getParameter(name);
    return v;
}

bool DefaultedHttpParams::removeParameter(std::string name) {
    return local->removeParameter(name);
}

HttpParams* DefaultedHttpParams::setParameter(std::string name, ValueBase *value) {
    return local->setParameter(name, value);
}

HttpParams* DefaultedHttpParams::getDefaults() {
    return defaults;
}
