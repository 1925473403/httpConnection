#include "HttpException.h"
#include "Value.h"
#include "RefCount.h"
#ifndef HTTPPARAMS_H
#define HTTPPARAMS_H
class HttpParams : public RefCount {
    public:
    virtual ~HttpParams() { }
    virtual ValueBase* getParameter(std::string name) = 0;
    virtual HttpParams* setParameter(std::string name, ValueBase *value) = 0;
    virtual bool removeParameter(std::string name) = 0;
    virtual long getLongParameter(std::string name, long defaultValue) = 0;
    virtual HttpParams* setLongParameter(std::string name, long value) = 0;
    virtual int getIntParameter(std::string name, int defaultValue) = 0;
    virtual HttpParams* setIntParameter(std::string name, int value) = 0;
    virtual double getDoubleParameter(std::string name, double defaultValue) = 0;
    virtual HttpParams* setDoubleParameter(std::string name, double value) = 0;
    virtual bool getBooleanParameter(std::string name, bool defaultValue) = 0;
    virtual HttpParams* setBooleanParameter(std::string name, bool value) = 0;
    virtual bool isParameterTrue(std::string name) = 0;
    virtual bool isParameterFalse(std::string name) = 0;
};
#endif
