#include "HttpException.h"
#include "Value.h"
#include "ClientPNames.h"
#include "CookiePolicy.h"
#include "HttpParams.h"
#ifndef HTTPCLIENTPARAMS_H
#include "HttpClientParams.h"
#endif
bool HttpClientParams::isRedirecting(HttpParams* params) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    return params->getBooleanParameter(ClientPNames::HANDLE_REDIRECTS, true);
}

void HttpClientParams::setRedirecting(HttpParams* params, bool value) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params->setBooleanParameter(ClientPNames::HANDLE_REDIRECTS, value);
}

bool HttpClientParams::isAuthenticating(HttpParams *params) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    return params->getBooleanParameter(ClientPNames::HANDLE_AUTHENTICATION, true);
}

void HttpClientParams::setAuthenticating(HttpParams* params, bool value) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params->setBooleanParameter(ClientPNames::HANDLE_AUTHENTICATION, value);
}

std::string HttpClientParams::getCookiePolicy(HttpParams *params) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    ValueBase *obj = params->getParameter(ClientPNames::COOKIE_POLICY);
    if (obj == NULL) return CookiePolicy::BEST_MATCH;
    std::string cookiePolicy("");
    cookiePolicy = type_cast<std::string>(obj, cookiePolicy);
    if (cookiePolicy.length() == 0) return CookiePolicy::BEST_MATCH;
    return cookiePolicy;
}

void HttpClientParams::setCookiePolicy(HttpParams* params, std::string cookiePolicy) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params->setParameter(ClientPNames::COOKIE_POLICY, new Value<std::string>(cookiePolicy));
}
