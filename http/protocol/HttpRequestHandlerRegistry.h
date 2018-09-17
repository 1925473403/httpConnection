#include "HttpException.h"
#ifndef HTTPREQUESTHANDLERREGISTRY_H
#define HTTPREQUESTHANDLERREGISTRY_H
class HttpRequestHandlerRegistry : public HttpRequestHandlerResolver {
    private :
        UriPatternMatcher matcher;
    public:
        bool matchUriRequestPattern(std::string &pattern, std::string &requestUri);
        HttpRequestHandlerRegistry();
        ~HttpRequestHandlerRegistry() { }
        void registerHandler(std::string &pattern, HttpRequestHandler *handler);
        void unregister(std::string &pattern);
        void setHandlers(unordered_map<std::string, ValueBase *> &map);
        HttpRequestHandler *lookup(std::string &requestURI);
};
#endif
