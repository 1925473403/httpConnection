#include "HttpException.h"
#ifndef RESPONSESERVER_H
#include "ResponseServer.h"
#endif
void ResponseServer::process(HttpResponse *response, HttpContext *context) throw (HttpException, IOException) {
    if (response == NULL) throw IllegalArgumentException("HTTP request may not be null");
    if (!response->containsHeader(HTTP::SERVER_HEADER)) {
        ValueBase *base = response->getParams()->getParameter(CoreProtocolPNames::ORIGIN_SERVER);
        std::string s = type_cast<Value<std::string>>(base, "");
        if (s.length() != 0) response->addHeader(HTTP::SERVER_HEADER, s);
    }
}
