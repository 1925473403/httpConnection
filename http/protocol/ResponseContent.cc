#include "HttpException.h"
#include "Integer.h"
#include "HTTP.h"
#include "HttpStatus.h"
#include "Value.h"
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
#ifndef RESPONSECONTENT_H
#include "ResponseContent.h"
#endif
void ResponseContent::process(HttpResponse *response, HttpContext *context) throw (HttpException, IOException) {
    if (response == NULL) throw IllegalArgumentException("HTTP response may not be null");
    if (response->containsHeader(HTTP::TRANSFER_ENCODING)) throw ProtocolException("Transfer-encoding header already present");
    if (response->containsHeader(HTTP::CONTENT_LEN)) throw ProtocolException("Content-Length header already present");
    ProtocolVersion *ver = response->getStatusLine()->getProtocolVersion();
    HttpEntity* entity = response->getEntity();
    if (entity == NULL) {
        int status = response->getStatusLine()->getStatusCode();
        if (status != HttpStatus::SC_NO_CONTENT && status != HttpStatus::SC_NOT_MODIFIED && status != HttpStatus::SC_RESET_CONTENT) response->addHeader(HTTP::CONTENT_LEN, "0");
        return;
    } else {
        int len = entity->getContentLength();
        if (entity->isChunked() && (!ver->lessEquals(*HttpVersion::HTTP_1_0))) {
                response->addHeader(HTTP::TRANSFER_ENCODING, HTTP::CHUNK_CODING);
        } else if (len >= 0) {
            response->addHeader(HTTP::CONTENT_LEN, Integer::toString(len));
        }
        if (entity->getContentType() != NULL && !response->containsHeader(HTTP::CONTENT_TYPE)) response->addHeader(entity->getContentType());
        if ((entity->getContentEncoding() != NULL) && (response->containsHeader(HTTP::CONTENT_ENCODING) == false)) response->addHeader(entity->getContentEncoding()); 
    }
}
