#include "HttpException.h"
#ifndef REQUESTTARGETHOST_H
#include "RequestTargetHost.h"
#endif
void RequestTargetHost::process(HttpRequest *request, HttpContext *context) throw (HttpException, IOException) {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    if (context == NULL) throw IllegalArgumentException("HTTP context may not be null");
    if (!request->containsHeader(HTTP::TARGET_HOST)) {
        ValueBase *obj = context->getAttribute(ExecutionContext::HTTP_TARGET_HOST);
        HttpHost *targethost = nullptr;
        targethost = type_cast<HttpHost *>(obj, targethost);
        if (targethost == NULL) {
            obj = context->getAttribute(ExecutionContext::HTTP_CONNECTION);
            HttpConnection *conn = nullptr;
            conn = type_cast<HttpConnection *>(obj, conn);
            HttpInetConnection *httpConn = dynamic_cast<HttpInetConnection *>(conn);
            if (httpConn != NULL) {
                InetAddress *address = httpConn->getRemoteAddress();
                nt port = httpConn->getRemotePort();
                if (address != NULL) targethost = new HttpHost(address->getHostName(), port);
            }
            if (targetHost == NULL) {
                ProtocolVersion *ver = request->getRequestLine()->getProtocolVersion();
                if (ver.lessEquals(HttpVersion::HTTP_1_0)) {
                    return;
                } else {
                    throw ProtocolException("Target host missing");
                }
            }
        }
        request.addHeader(HTTP::TARGET_HOST, targethost->toHostString());
    }
}
