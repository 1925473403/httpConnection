#include "HttpException.h"
#ifndef DEFAULTHTTPRESPONSEFACTORY_H
#include "DefaultHttpResponseFactory.h"
#endif
DefaultHttpResponseFactory::DefaultHttpResponseFactory() : DefaultHttpResponseFactory(EnglishReasonPhraseCatalog::INSTANCE) {
}
DefaultHttpResponseFactory::~DefaultHttpResponseFactory() {
    if (reasonCatalog) reasonCatalog->unref();
}
DefaultHttpResponseFactory::DefaultHttpResponseFactory(ReasonPhraseCatalog *catalog) {
    if (catalog == NULL) throw IllegalArgumentException("HTTP version may not be null");
    reasonCatalog = catalog;
    if (catalog) catalog->ref();
}
HttpResponse* DefaultHttpResponseFactory::newHttpResponse(StatusLine* statusline, HttpContext *context) {
    if (statusline == NULL) throw IllegalArgumentException("Status line may not be null");
    Locale *loc = determineLocale(context);
    return new BasicHttpResponse(statusline, reasonCatalog, loc);
}
HttpResponse* DefaultHttpResponseFactory::newHttpResponse(ProtocolVersion *ver, int status, HttpContext *context) {
    if (ver == NULL) throw IllegalArgumentException("HTTP version may not be null");
    Locale *loc = determineLocale(context);
    std::string reason = reasonCatalog->getReason(status, loc);
    StatusLine *statusline = new BasicStatusLine(ver, status, reason);
    HttpResponse* res= new BasicHttpResponse(statusline, reasonCatalog, loc);
    statusline->unref();
    return res;
}
Locale* DefaultHttpResponseFactory::determineLocale(HttpContext *context) {
    return Locale::getDefault();
}
