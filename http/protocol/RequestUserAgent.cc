#include "HttpException.h"
#include "Value.h"
#include "HttpRequest.h"
#include "HttpContext.h"
#include "HttpParams.h"
#include "CoreProtocolPNames.h"
#include "ProtocolVersion.h"
#include "HttpProtocolParams.h"
#include "HTTP.h"
#ifndef REQUESTUSERAGENT_H
#include "RequestUserAgent.h"
#endif
void RequestUserAgent::process(HttpRequest* request, HttpContext *context) throw (HttpException, IOException) {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    if (context == NULL) throw IllegalArgumentException("HTTP context may not be null");
    if (!request->containsHeader(HTTP::USER_AGENT)) {
        std::string useragent = HttpProtocolParams::getUserAgent(request->getParams());
        if (useragent.length() > 0) request->addHeader(HTTP::USER_AGENT, useragent);
    }
}
