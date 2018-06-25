#include "HttpException.h"
#ifndef ABSTRACTHTTPPARAMS_H
#define ABSTRACTHTTPPARAMS_H
class AbstractHttpParams : public HttpParams {
    protected:
        AbstractHttpParams() { }
    public:
        virtual ~AbstractHttpParams() { }
        long getLongParameter(std::string, long defaultValue);
        HttpParams* setLongParameter(std::string, long defaultValue);
        int getIntParameter(std::string, int defaultValue);
        HttpParams* setIntParameter(std::string, int defaultValue);
        double getDoubleParameter(std::string, double);
        HttpParams* setDoubleParameter(std::string, double);
        bool getBooleanParameter(std::string, bool);
        HttpParams* setBooleanParameter(std::string, bool);
        bool isParameterTrue(std::string );
        bool isParameterFalse(std::string );
};
#endif
