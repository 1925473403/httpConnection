#include "HttpException.h"
#ifndef REQUESTCONTENT_H
#include "RequestContent.h"
#endif
void RequestContent::process(HttpRequest *request, HttpContext *context) throw (HttpException, IOException) {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    HttpEntityEnclosingRequest* r = dynamic_cast<HttpEntityEnclosingRequest *>(request);
    if (r != NULL) {
        if (request->containsHeader(HTTP::TRANSFER_ENCODING)) throw ProtocolException("Transfer-encoding header already present");
        if (request->containsHeader(HTTP::CONTENT_LEN)) throw ProtocolException("Content-Length header already present");
        ProtocolVersion *ver = request->getRequestLine()->getProtocolVersion();
        HttpEntity* entity = r->getEntity();
        if (entity == NULL) {
            request->addHeader(HTTP::CONTENT_LEN, "0"); 
            return;
        }
        if (entity->isChunked() || entity->getContentLength() < 0) {
            if (ver->lessEquals(*HttpVersion::HTTP_1_0)) {
                throw ProtocolException("Chunked transfer encoding not allowed for %s" + ver->toString().c_str());
            }
            request->addHeader(HTTP::TRANSFER_ENCODING, HTTP::CHUNK_CODING);
        } else {
            request->addHeader(HTTP::CONTENT_LEN, Integer::toString(entity->getContentLength()));
        }
        if (entity->getContentType() != NULL && !request->containsHeader(HTTP::CONTENT_TYPE)) request->addHeader(entity->getContentType());
        if (entity->getContentEncoding() != NULL !request->containsHeader(HTTP::CONTENT_ENCODING)) request->addHeader(entity->getContentEncoding()); 
    }
}
