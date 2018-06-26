#include "HttpException.h"
#ifndef HTTPREQUESTHANDLERREGISTRY_H
#include "HttpRequestHandlerRegistry.H"
#endif
bool HttpRequestHandlerRegistry::matchUriRequestPattern(std::string pattern, std::string requestUri) {
    return matcher.matchUriRequestPattern(pattern, requestUri);
}
void HttpRequestHandlerRegistry::registerHandler(std::string pattern, HttpRequestHandler *handler) {
    matcher.registerUri(pattern, new Value<HttpRequestHandler *>(handler));
}
void HttpRequestHandlerRegistry::unregister(std::string pattern) {
    matcher.unregister(pattern);
}
void HttpRequestHandlerRegistry::setHandlers(unordered_map<std::string, ValueBase *> &map) {
    matcher.setHandlers(map);
}
HttpRequestHandler *HttpRequestHandlerRegistry::lookup(std::string requestURI) {
    HttpRequestHandler *handler = type_cast<HttpRequestHandler *>(matcher.lookup(requestUri));
    return handler;
}
