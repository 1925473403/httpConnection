#include "HttpException.h"
#include "Value.h"
#include "HttpParams.h"
#include "ProtocolVersion.h"
#include "RequestLine.h"
#include "NameValuePair.h"
#include "HeaderElement.h"
#include "Header.h"
#include "HeaderIterator.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "StatusLine.h"
#include "HttpEntity.h"
#include "HttpMessage.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpContext.h"
#include "UriPatternMatcher.h"
#include "HttpRequestHandler.h"
#include "HttpRequestHandlerResolver.h"
#ifndef HTTPREQUESTHANDLERREGISTRY_H
#include "HttpRequestHandlerRegistry.h"
#endif
bool HttpRequestHandlerRegistry::matchUriRequestPattern(std::string &pattern, std::string &requestUri) {
    return matcher.matchUriRequestPattern(pattern, requestUri);
}
void HttpRequestHandlerRegistry::registerHandler(std::string &pattern, HttpRequestHandler *handler) {
    matcher.registerUri(pattern, new Value<HttpRequestHandler *>(handler));
}
void HttpRequestHandlerRegistry::unregister(std::string &pattern) {
    matcher.unregister(pattern);
}
void HttpRequestHandlerRegistry::setHandlers(unordered_map<std::string, ValueBase *> &map) {
    matcher.setHandlers(map);
}
HttpRequestHandler *HttpRequestHandlerRegistry::lookup(std::string &requestUri) {
    HttpRequestHandler *handler = type_cast<HttpRequestHandler *>(matcher.lookup(requestUri), NULL);
    return handler;
}
