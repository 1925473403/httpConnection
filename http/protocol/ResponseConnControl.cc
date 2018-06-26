#include "HttpException.h"
#include "Value.h"
#include "HttpRequest.h"
#include "HttpContext.h"
#include "HttpParams.h"
#include "CoreProtocolPNames.h"
#include "ProtocolVersion.h"
#include "HttpVersion.h"
#include "HttpProtocolParams.h"
#include "HTTP.h"
#ifndef RESPONSECONNCONTROL_H
#include "ResponseConnControl.h"
#endif
void ResponseConnControl::process(HttpResponse *response, HttpContext *context) throw (HttpException, IOException) {
    if (response == NULL) throw IllegalArgumentException("HTTP response may not be null");
    if (context == NULL) throw IllegalArgumentException("HTTP context may not be null");
    int status = response->getStatusLine()->getStatusCode();
    if (status == HttpStatus::SC_BAD_REQUEST ||
        status == HttpStatus::SC_REQUEST_TIMEOUT ||
        status == HttpStatus::SC_LENGTH_REQUIRED ||
        status == HttpStatus::SC_REQUEST_TOO_LONG ||
        status == HttpStatus::SC_REQUEST_URI_TOO_LONG ||
        status == HttpStatus::SC_SERVICE_UNAVAILABLE ||
        status == HttpStatus::SC_NOT_IMPLEMENTED) {
        response->setHeader(HTTP::CONN_DIRECTIVE, HTTP::CONN_CLOSE); 
        return;
    }
    HttpEntity* entity = response->getEntity();
    if (entity != NULL) {
        ProtocolVersion *ver = response->getStatusLine()->getProtocolVersion();
        if (entity->getContentLength() < 0 && (!entity->isChunked() || ver->lessEquals(HttpVersion::HTTP_1_0))) {
            response->setHeader(HTTP::CONN_DIRECTIVE, HTTP::CONN_CLOSE);
            return;
        }
    }
    HttpRequest* request = (HttpRequest *) context->getAttribute(ExecutionContext::HTTP_REQUEST);
    if (request != NULL) {
        Header *header = request->getFirstHeader(HTTP::CONN_DIRECTIVE);
        if (header != NULL) response->setHeader(HTTP::CONN_DIRECTIVE, header.getValue());
    }
}
