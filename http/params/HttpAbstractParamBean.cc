#include "HttpException.h"
#include "HttpParams.h"
#ifndef HTTPABSTRACTPARAMBEAN_H
#include "HttpAbstractParamBean.h"
#endif
HttpAbstractParamBean::HttpAbstractParamBean(HttpParams *p) { 
    if (p == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params = p;
}
HttpAbstractParamBean::~HttpAbstractParamBean() {
}
