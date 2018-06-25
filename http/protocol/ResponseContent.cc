#include "HttpException.h"
#ifndef RESPONSECONTENT_H
#include "ResponseContent.h"
#endif
void ResponseContent::process(HttpRequest *response, HttpContext *context) throw (HttpException, IOException) {
    if (response == NULL) throw IllegalArgumentException("HTTP response may not be null");
    if (response->containsHeader(HTTP::TRANSFER_ENCODING)) throw ProtocolException("Transfer-encoding header already present");
    if (response->containsHeader(HTTP::CONTENT_LEN)) throw ProtocolException("Content-Length header already present");
    ProtocolVersion *ver = response->getStatusLine()->getProtocolVersion();
    HttpEntity* entity = r->getEntity();
    if (entity == NULL) {
        int status = response->getStatusLine()->getStatusCode();
        if (status != HttpStatus::SC_NO_CONTENT && status != HttpStatus::SC_NOT_MODIFIED && status != HttpStatus::SC_RESET_CONTENT) response->addHeader(HTTP::CONTENT_LEN, "0");
        return;
    } else {
        int len = entity->getContentLength();
        if (entity->isChunked() && (!ver->lessEquals(*HttpVersion::HTTP_1_0)) {
                response->addHeader(HTTP::TRANSFER_ENCODING, HTTP::CHUNK_CODING);
        } else if (len >= 0) {
            response->addHeader(HTTP::CONTENT_LEN, Integer::toString(len));
        }
        if (entity->getContentType() != NULL && !response->containsHeader(HTTP::CONTENT_TYPE)) response->addHeader(entity->getContentType());
        if (entity->getContentEncoding() != NULL !response->containsHeader(HTTP::CONTENT_ENCODING)) response->addHeader(entity->getContentEncoding()); 
    }
}
