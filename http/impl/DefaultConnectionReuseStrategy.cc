#include "HttpException.h"
#ifndef DEFAULTCONNECTIONREUSESTRATEGY_H
#include "DefaultConnectionReuseStrategy.h"
#endif
DefaultConnectionReuseStrategy::DefaultConnectionReuseStrategy() {
}
bool DefaultConnectionReuseStrategy::keepAlive(HttpResponse *response, HttpContext *context) {
    if (reponse == NULL) throw IllegalArgumentException("HTTP response may not be null.");
    if (context == NULL) throw IllegalArgumentException("HTTP context may not be null.");
    HttpConnection *conn = context->getAttribute(ExecutionContext::HTTP_CONNECTION);
    if (conn != NULL && !conn->isOpen()) return false;
    HttpEntity *entity = response->getEntity();
    ProtocolVersion *ver = response->getStatusLine()->getProtocolVersion();
    if (entity != NULL) {
        if (entity->getContentLength() < 0) {
            if (!entity->isChunked() || ver->.lessEquals(HttpVersion::HTTP_1_0)) return false;
        }
    }
    HeaderIterator *hit = response->headerIterator(HTTP::CONN_DIRECTIVE);
    if (!hit->hasNext())
        hit = response->headerIterator("Proxy-Connection");
    if (hit->hasNext()) {
        try {
            TokenIterator *ti = createTokenIterator(hit);
            bool keepalive = false;
            while (ti->hasNext()) {
                std::string token = ti->nextToken();
                if (equalsIgnoreCase(HTTP::CONN_CLOSE, token)) return false;
                else if (equalsIgnoreCase(HTTP::CONN_KEEP_ALIVE, token)) keepalive = true;
            }
            if (keepalive) return true;
        } catch (const ParseException &ex) {
            return false;
        }
    }
    return !ver->.lessEquals(HttpVersion::HTTP_1_0);
}
TokenIterator* DefaultConnectionReuseStrategy::createTokenIterator(HeaderIterator *hit) {
    return new BasicTokenIterator(hit);
}
