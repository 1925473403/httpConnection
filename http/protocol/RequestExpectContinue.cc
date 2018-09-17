#include "HttpException.h"
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
#ifndef REQUESTCONNCONTROL_H
#include "RequestExpectContinue.h"
#endif
void RequestExpectContinue::process(HttpRequest *request, HttpContext *context) throw (HttpException, IOException) {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    HttpEntityEnclosingRequest* heer = dynamic_cast<HttpEntityEnclosingRequest *>(request);
    if (heer != NULL) {
        HttpEntity *entity = heer->getEntity();
        if (entity != NULL && entity->getContentLength() != 0) {
            ProtocolVersion *ver = request->getRequestLine()->getProtocolVersion();
            if (HttpProtocolParams::useExpectContinue(request->getParams()) && !ver->lessEquals(*HttpVersion::HTTP_1_0)) {
                request->addHeader(HTTP::EXPECT_DIRECTIVE, HTTP::EXPECT_CONTINUE);
            }
        }
    }
}
