#include "HttpParams.h"
#include "Value.h"
#ifndef ABSTRACTHTTPPARAMS_H
#include "AbstractHttpParams.h"
#endif
long AbstractHttpParams::getLongParameter(std::string name, long defaultValue) {
    try {
        ValueBase *obj = getParameter(name);
        Value<long> *objValue = dynamic_cast<Value<long> *> (obj);
        if (objValue != NULL) return objValue->value();
    } catch (...) {
    }
    return defaultValue;
}
HttpParams* AbstractHttpParams::setLongParameter(std::string name, long defaultValue) {
    ValueBase *v = new Value<long>(defaultValue);
    setParameter(name, v);
    v->unref();
    return this;
}
int AbstractHttpParams::getIntParameter(std::string name, int defaultValue) {
    try {
        ValueBase *obj = getParameter(name);
        Value<int> *objValue = dynamic_cast<Value<int> *> (obj);
        if (objValue != NULL) return objValue->value();
    } catch (...) {
    }
    return defaultValue;
}
HttpParams* AbstractHttpParams::setIntParameter(std::string name, int defaultValue) {
    ValueBase *v = new Value<int>(defaultValue);
    setParameter(name, v);
    v->unref();
    return this;
}
double AbstractHttpParams::getDoubleParameter(std::string name, double defaultValue) {
    try {
        ValueBase* obj = getParameter(name);
        Value<double>  *objValue = dynamic_cast<Value<double> *> (obj);
        if (objValue != NULL) return objValue->value();
    } catch (...) {
    }
    return defaultValue;
}
HttpParams* AbstractHttpParams::setDoubleParameter(std::string name, double defaultValue) {
    ValueBase *v = new Value<double>(defaultValue);
    setParameter(name, v);
    v->unref();
    return this;
}
bool AbstractHttpParams::getBooleanParameter(std::string name, bool defaultValue) {
    try {
        ValueBase *obj = getParameter(name);
        Value<bool> *objValue = dynamic_cast<Value<bool> *> (obj);
        if (objValue != NULL) return objValue->value();
    } catch (...) {
    }
    return defaultValue;
}

HttpParams* AbstractHttpParams::setBooleanParameter(std::string name, bool defaultValue) {
    ValueBase *v = new Value<bool>(defaultValue);
    setParameter(name, v);
    v->unref();
    return this;
}
bool AbstractHttpParams::isParameterTrue(std::string name) {
    return getBooleanParameter(name, false);
}
bool AbstractHttpParams::isParameterFalse(std::string name) {
    return !getBooleanParameter(name, false);
}
