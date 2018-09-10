#include "HttpException.h"
#ifndef COOKIESPECPARAMBEAN_H
#define COOKIESPECPARAMBEAN_H
class CookieSpecParamBean : public HttpAbstractParamBean {
    public:
    CookieSpecParamBean(HttpParams *params) ;
    void setDatePatterns(vector<std::string> &patterns);
    void setSingleHeader(bool singleHeader);
};
#endif
