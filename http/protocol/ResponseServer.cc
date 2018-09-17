#include "HttpException.h"
#include "HTTP.h"
#include "HttpStatus.h"
#include "Value.h"
#include "HttpParams.h"
#include "ProtocolVersion.h"
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
#include "CoreProtocolPNames.h"
#include "HttpResponseInterceptor.h"
#ifndef RESPONSESERVER_H
#include "ResponseServer.h"
#endif
void ResponseServer::process(HttpResponse *response, HttpContext *context) throw(HttpException, IOException) {
    if (response == NULL) throw IllegalArgumentException("HTTP request may not be null");
    if (!response->containsHeader(HTTP::SERVER_HEADER)) {
        ValueBase *base = response->getParams()->getParameter(CoreProtocolPNames::ORIGIN_SERVER);
        std::string s  = type_cast<std::string>(base, "");
        if (s.length() != 0) response->addHeader(HTTP::SERVER_HEADER, s);
    }
}
