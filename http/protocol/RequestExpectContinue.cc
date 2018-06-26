#include "HttpException.h"
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
            if (HttpProtocolParams::useExpectContinue(request->getParams()) && !ver->lessEquals(HttpVersion::HTTP_1_0)) {
                request->addHeader(HTTP::EXPECT_DIRECTIVE, HTTP::EXPECT_CONTINUE);
            }
        }
    }
}
