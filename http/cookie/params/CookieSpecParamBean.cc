#include "HttpParams.h"
#include "HttpAbstractParamBean.h"
#include "CookieSpecPNames.h"
#ifndef COOKIESPECPARAMBEAN_H
#include "CookieSpecParamBean.h"
#endif
CookieSpecParamBean::CookieSpecParamBean(HttpParams *params) : HttpAbstractParamBean(params) { }
void CookieSpecParamBean::setDatePatterns(std::vector<std::string> &patterns) {
    //Value<vector<std::string>> vv(patterns);
    //params->setParameter(CookieSpecPNames::DATE_PATTERNS, &vv);
}
void CookieSpecParamBean::setSingleHeader(bool singleHeader) {
    params->setBooleanParameter(CookieSpecPNames::SINGLE_COOKIE_HEADER, singleHeader);
}
