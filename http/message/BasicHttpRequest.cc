#include "CharArrayBuffer.h"
#include "ProtocolVersion.h"
#include "RequestLine.h"
#include "StatusLine.h"
#include "Header.h"
#include "FormattedHeader.h"
#include "LineFormatter.h"
#include "Integer.h"
#include "BasicLineFormatter.h"
#include "BasicRequestLine.h"
#include "HttpParams.h"
#include "CoreProtocolPNames.h"
#include "HttpProtocolParams.h"
#include "HeaderIterator.h"
#include "BasicListHeaderIterator.h"
#include "HeaderGroup.h"
#include "HttpMessage.h"
#include "HttpRequest.h"
#include "AbstractHttpMessage.h"
#ifndef BASICHTTPMESSAGE_H
#include "BasicHttpRequest.h"
#endif
BasicHttpRequest::BasicHttpRequest(std::string m, std::string u) {
    if (method.length() == 0) throw IllegalArgumentException("Method name may not be null");
    if (uri.length() == 0) throw IllegalArgumentException("Request URI may not be null");
    method = m;
    uri = u;
    requestline = 0;
}

BasicHttpRequest::BasicHttpRequest(std::string m, std::string u, ProtocolVersion* ver):method(m), uri(u) {
    requestline = new BasicRequestLine(m, u, ver);
}

BasicHttpRequest::BasicHttpRequest(RequestLine *r) {
    if (requestline == NULL) throw IllegalArgumentException("Request line may not be null");
    requestline = r;
    method = requestline->getMethod();
    uri = requestline->getUri();
}

ProtocolVersion* BasicHttpRequest::getProtocolVersion() {
    if (requestline != NULL) return requestline->getProtocolVersion();
    return HttpProtocolParams::getVersion(AbstractHttpMessage::getParams());
}

RequestLine* BasicHttpRequest::getRequestLine() {
    if (requestline != NULL) return requestline;
    ProtocolVersion *ver = HttpProtocolParams::getVersion(AbstractHttpMessage::getParams());
    return new BasicRequestLine(method, uri, ver);
}
