#include "HttpException.h"
#ifndef DEFAULTHTTPREQUESTFACTORY_H
#include "DefaultHttpRequestFactory.h"
#endif
vector<std::string> DefaultHttpRequestFactory::RFC2616_COMMON_METHODS({"GET"});
vector<std::string> DefaultHttpRequestFactory::RFC2616_ENTITY_ENC_METHODS({"POST", "PUT"});
vector<std::string> DefaultHttpRequestFactory::RFC2616_SPECIAL_METHODS({"HEAD", "OPTIONS", "DELETE", "TRACE"});
DefaultHttpRequestFactory::DefaultHttpRequestFactory() { }
bool DefaultHttpRequestFactory::isOneOf(vector<std::string> &methods, std::string method) {
    for (int i = 0; i < methods.size(); i++) {
        if (equalsIgnoreCase(methods[i], method)) return true;
    }
    return false;
}
HttpRequest* DefaultHttpRequestFactory::newHttpRequest(RequestLine* requestline) throw (MethodNotSupportedException) {
    if (requestline == NULL) throw IllegalArgumentException("Request line may not be null");
    std::string method = requestline->getMethod();
    if (isOneOf(RFC2616_COMMON_METHODS, method)) return new BasicHttpRequest(requestline);
    else if (isOneOf(RFC2616_ENTITY_ENC_METHODS, method)) return new BasicHttpEntityEnclosingRequest(requestline);
    else if (isOneOf(RFC2616_SPECIAL_METHODS, method)) return new BasicHttpRequest(requestline);
    else throw MethodNotSupportedException("Not supported method: %s", method.c_str());
}

HttpRequest* DefaultHttpRequestFactory::newHttpRequest(std::string method, std::string uri) throw (MethodNotSupportedException) {
    if (isOneOf(RFC2616_COMMON_METHODS, method)) return new BasicHttpRequest(method, uri);
    else if (isOneOf(RFC2616_ENTITY_ENC_METHODS, method)) return new BasicHttpEntityEnclosingRequest(method, uri);
    else if (isOneOf(RFC2616_SPECIAL_METHODS, method)) return new BasicHttpRequest(method, uri);
    else thow MethodNotSupportedException("Not supported method: %s", method.c_str());
}
