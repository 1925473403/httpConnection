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
    setParameter(name, new Value<long>(defaultValue));
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
    setParameter(name, new Value<int>(defaultValue));
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
    setParameter(name, new Value<double>(defaultValue));
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
    setParameter(name, new Value<bool>(defaultValue));
    return this;
}
bool AbstractHttpParams::isParameterTrue(std::string name) {
    return getBooleanParameter(name, false);
}
bool AbstractHttpParams::isParameterFalse(std::string name) {
    return !getBooleanParameter(name, false);
}
