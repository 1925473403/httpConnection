#include "HttpException.h"
#ifndef DEFAULTHTTPREQUESTFACTORY_H
#define DEFAULTHTTPREQUESTFACTORY_H
class DefaultHttpRequestFactory : public HttpRequestFactory {
    private:
        static vector<std::string> RFC2616_COMMON_METHODS;
        static vector<std::string> RFC2616_ENTITY_ENC_METHODS;
        static vector<std::string> RFC2616_SPECIAL_METHODS;
    public:
        DefaultHttpRequestFactory() ;
        bool isOneOf(vector<std::string> &methods, std::string method);
        HttpRequest* newHttpRequest(RequestLine* requestline) throw (MethodNotSupportedException);
        HttpRequest* newHttpRequest(std::string method, std::string uri) throw (MethodNotSupportedException);
};
#endif
