#include "HttpException.h"
#ifndef REQUESTCONNCONTROL_H
#include "RequestConnControl.h"
#endif
void RequestConnControl::process(HttpRequest *request, HttpContext *context) throw (HttpException, IOException) {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    if (!request->containsHeader(HTTP::CONN_DIRECTIVE)) {
        request->addHeader(HTTP::CONN_DIRECTIVE, HTTP::CONN_KEEP_ALIVE);
    }
}
