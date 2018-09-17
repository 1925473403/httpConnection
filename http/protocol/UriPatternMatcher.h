#include "HttpException.h"
#ifndef URIPATTERNMATCHER_H
#define URIPATTERNMATCHER_H
class UriPatternMatcher {
    private:
        unordered_map<std::string, ValueBase *> handlerMap;
        bool starts_with(std::string &requestUri, std::string &pattern);
        bool ends_with(std::string &requestUri, std::string &pattern);
    public:
        bool matchUriRequestPattern(std::string &pattern, std::string &requestUri);
        UriPatternMatcher() { }
        ~UriPatternMatcher() { }
        void registerUri(std::string &pattern, ValueBase *handler);
        void unregister(std::string &pattern);
        void setHandlers(unordered_map<std::string, ValueBase *> &map);
        ValueBase* lookup(std::string &requestURI);
};
#endif
