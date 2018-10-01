#include "HttpException.h"
#include "HTTP.h"
#include "HttpStatus.h"
#include "Value.h"
#include "Integer.h"
#include "HttpParams.h"
#include "ProtocolVersion.h"
#include "HttpVersion.h"
#include "CoreProtocolPNames.h"
#include "HttpProtocolParams.h"
#include "RequestLine.h"
#include "NameValuePair.h"
#include "HeaderElement.h"
#include "Header.h"
#include "HeaderIterator.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "StatusLine.h"
#include "HttpContext.h"
#include "HttpEntity.h"
#include "HttpMessage.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpEntityEnclosingRequest.h"
#include "HttpRequestInterceptor.h"
#ifndef REQUESTCONTENT_H
#include "RequestContent.h"
#endif
void RequestContent::process(HttpRequest *request, HttpContext *context) throw (HttpException, IOException) {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    HttpEntityEnclosingRequest* r = dynamic_cast<HttpEntityEnclosingRequest *>(request);
    if (r != NULL) {
        if (request->containsHeader(HTTP::TRANSFER_ENCODING)) throw ProtocolException("Transfer-encoding header already present");
        if (request->containsHeader(HTTP::CONTENT_LEN)) throw ProtocolException("Content-Length header already present");
        RequestLine *requestline = request->getRequestLine();
        ProtocolVersion *ver = requestline->getProtocolVersion();
        requestline->unref();
        HttpEntity* entity = r->getEntity();
        if (entity == NULL) {
            request->addHeader(HTTP::CONTENT_LEN, "0"); 
            return;
        }
        if (entity->isChunked() || entity->getContentLength() < 0) {
            if (ver->lessEquals(*HttpVersion::HTTP_1_0)) {
                char errMsg[512] = {  0 };
                snprintf(errMsg, 511, "Chunked transfer encoding not allowed for %s", ver->toString().c_str());
                ver->unref();
                throw ProtocolException((const char *)errMsg);
            }
            request->addHeader(HTTP::TRANSFER_ENCODING, HTTP::CHUNK_CODING);
        } else {
            request->addHeader(HTTP::CONTENT_LEN, Integer::toString(entity->getContentLength()));
        }
        if (entity->getContentType() != NULL && !request->containsHeader(HTTP::CONTENT_TYPE)) request->addHeader(entity->getContentType());
        if (entity->getContentEncoding() != NULL && !request->containsHeader(HTTP::CONTENT_ENCODING)) request->addHeader(entity->getContentEncoding()); 
        ver->unref();
    }
}
