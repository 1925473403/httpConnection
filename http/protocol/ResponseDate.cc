#include "HttpException.h"
#include "Value.h"
#include "HttpDateGenerator.h"
#include "ProtocolVersion.h"
#include "StatusLine.h"
#include "HttpParams.h"
#include "HeaderIterator.h"
#include "HeaderElement.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "Header.h"
#include "HttpStatus.h"
#include "HttpEntity.h"
#include "HttpMessage.h"
#include "HttpResponse.h"
#include "HttpContext.h"
#include "HttpResponseInterceptor.h"
#include "HTTP.h"
#ifndef RESPONSEDATE_H
#include "ResponseDate.h"
#endif
HttpDateGenerator ResponseDate::DATE_GENERATOR;
void ResponseDate::process(HttpResponse *response, HttpContext *context) throw(HttpException, IOException) {
    if (response == NULL) throw IllegalArgumentException ("HTTP request may not be null.");
    int status = response->getStatusLine()->getStatusCode();
    if ((status >= HttpStatus::SC_OK) && !response->containsHeader(HTTP::DATE_HEADER)) {
        std::string httpdate = DATE_GENERATOR.getCurrentDate();
        response->setHeader(HTTP::DATE_HEADER, httpdate);
    }
}
