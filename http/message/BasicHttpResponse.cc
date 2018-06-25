#include "CharArrayBuffer.h"
#include "ProtocolVersion.h"
#include "StatusLine.h"
#include "HttpEntity.h"
#include "Locale.h"
#include "HttpMessage.h"
#include "HttpResponse.h"
#include "AbstractHttpMessage.h"
#ifndef BASICHTTPRESPONSE_H
#include "BasicHttpResponse.h"
#endif
BasicHttpResponse::BasicHttpResponse(StatusLine *s, ReasonPhraseCatalog *e, Locale *l) : statusline(s), reasonCatalog(e) {
    if (statusline == NULL) throw IllegalArgumentException("Status line may not be null.");
    locale = ((l != NULL) ? l: Locale::getDefaults());
}

BasicHttpResponse::BasicHttpResponse(StatusLine *s) : BasicHttpResponse(s,  NULL, NULL) {
}

BasicHttpResponse::BasicHttpResponse(ProtocolVersion *p, int code, std::string reason) : BasicHttpResponse(new BasicStatusLine(p, code, reason), NULL, NULL) {
}

ProtocolVersion* BasicHttpResponse::getProtocolVersion() {
    return statusline->getProtocolVersion();
}

StatusLine* BasicHttpResponse::getStatusLine() {
    return statusline;
}

HttpEntity* BasicHttpResponse::getEntity() {
    return entity;
}

Locale* BasicHttpResponse::getLocale() {
    return locale;
}

void BasicHttpResponse::setStatusLine(StatusLine *s) {
    if (s == NULL) throw IllegalArgumentException("Status line may not be null.");
    statusline = s;
}

void BasicHttpResponse::setStatusLine(ProtocolVersion *p, int code) {
    statusline = new BasicStatusLine(ver, code, getReason(code));
}

void BasicHttpResponse::setStatusLine(ProtocolVersion *p, int code, std::string reason) {
    statusline = new BasicStatusLine(ver, code, reason);
}

void BasicHttpResponse::setStatusCode(int code) {
    ProtocolVersion *ver = statusline->getProtocolVersion();
    statusline = new BasicStatusLine(ver, code, getReason(code));
}

void BasicHttpResponse::setReasonPhrase(std::string reason) {
    if (reason.length() > 0 && (reason.find('\n') != std::string::npos && reason.find('\r') != std::string::npos)) throw IllegalArgumentException("Line break in reason phrase.");
    statusline = new BasicStatusLine(statusline->getProtocolVersion(), statusline->getStatusCode(), reason);
}

void BasicHttpResponse::setEntity(HttpEntity *e) {
    entity = entity;
}

void BasicHttpResponse::setLocale(Locale *l) {
    if (l == NULL) throw IllegalArgumentException("Locale may not be null.");
    locale = l;
    int code = statusline->getStatusCode();
    statusline = new BasicStatusLine(statusline->getProtocolVersion(), code, getReason(code));
}

std::string BasicHttpResponse::getReason(int code) {
    if (reasonCatalog == NULL) return "";
    return reasonCatalog->getReason(code, locale);
}
