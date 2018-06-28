#include "HttpException.h"
#ifndef HTTPCLIENTPARAMS_H
#define HTTPCLIENTPARAMS_H
class HttpClientParams {
        HttpClientParams() { }
    public:
        static bool isRedirecting(HttpParams* params);
        static void setRedirecting(HttpParams* params, bool value);
        static bool isAuthenticating(HttpParams *params);
        static void setAuthenticating(HttpParams* params, bool value);
        static std::string getCookiePolicy(HttpParams *params);
        static void setCookiePolicy(HttpParams* params, std::string cookiePolicy);
};
#endif
