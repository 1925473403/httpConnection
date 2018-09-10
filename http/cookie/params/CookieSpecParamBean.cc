#include "HttpParams.h"
#ifndef COOKIESPECPARAMBEAN_H
#include "CookieSpecParamBean.h"
#endif
CookieSpecParamBean(HttpParams *params) : HttpAbstractParamBean(params) {
}
void CookieSpecParamBean::setDatePatterns(vector<std::string> &patterns) {
    params->setParameter(CookieSpecPNames::DATE_PATTERNS, patterns);
}
void CookieSpecParamBean::setSingleHeader(bool singleHeader) {
    params->setBooleanParameter(CookieSpecPNames::SINGLE_COOKIE_HEADER, singleHeader);
}
