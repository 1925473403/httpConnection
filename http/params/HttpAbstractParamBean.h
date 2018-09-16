#include "HttpException.h"
#include "RefCount.h"
#ifndef HTTPABSTRACTPARAMBEAN_H
#define HTTPABSTRACTPARAMBEAN_H
class HttpAbstractParamBean: public RefCount {
    protected:
    HttpParams *params;
    public:
    HttpAbstractParamBean(HttpParams *params) ;
    virtual ~HttpAbstractParamBean() = 0;
};
#endif
