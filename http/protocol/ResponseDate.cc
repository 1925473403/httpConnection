#include "HttpDateGenerator.h"
#ifndef RESPONSEDATE_H
#include "ResponseDate.h"
#endif
HttpDateGenerator ResponseDate::DATE_GENERATOR;
void ResponseDate::process(HttpRequest *response, HttpContext *context) throw (HttpException, IOException) {
    if (response == NULL) throw IllegalArgumentException ("HTTP request may not be null.");
    int status = response->getStatusLine()->getStatusCode();
    if ((status >= HttpStatus::SC_OK) && !response->containsHeader(HTTP::DATE_HEADER)) {
        std::string httpdate = DATE_GENERATOR.getCurrentDate();
        response->setHeader(HTTP::DATE_HEADER, httpdate);
    }
}
