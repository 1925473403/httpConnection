#include "HttpException.h"
#ifndef HTTPABSTRACTPARAMBEAN_H
#define HTTPABSTRACTPARAMBEAN_H
class HttpAbstractParamBean {
    protected:
    HttpParams *params;
    public:
    HttpAbstractParamBean(HttpParams *params) ;
    virtual ~HttpAbstractParamBean() = 0;
};
#endif
