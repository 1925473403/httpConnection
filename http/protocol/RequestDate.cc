#include "HttpDateGenerator.h"
#ifndef REQUESTDATE_H
#include "RequestDate.h"
#endif
HttpDateGenerator RequestDate::DATE_GENERATOR;
void RequestDate::process(HttpRequest *request, HttpContext *context) throw (HttpException, IOException) {
    if (request == NULL) throw IllegalArgumentException ("HTTP request may not be null.");
    HttpEntityEnclosingRequest *r = dynamic_cast<HttpEntityEnclosingRequest *>(request);
    if (r != NULL && !request->containsHeader(HTTP::DATE_HEADER)) {
        std::string httpdate = DATE_GENERATOR.getCurrentDate();
        request.setHeader(HTTP::DATE_HEADER, httpdate);
    }
}
