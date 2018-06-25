#include "HttpException.h"
#ifndef BASICHTTPENTITYENCLOSINGREQUST_H
#include "BasicHttpEntityEnclosingRequest.h"
#endif
class BasicHttpEntityEnclosingRequest :public BasicHttpRequest , public HttpEntityEnclosingRequest {
    private:
        HttpEntity *entity;
    public:
BasicHttpEntityEnclosingRequest::BasicHttpEntityEnclosingRequest(std::string method, std::string uri) : BasicHttpRequest(method, uri) {
}
BasicHttpEntityEnclosingRequest::BasicHttpEntityEnclosingRequest(std::string method, std::string uri, ProtocolVersion *ver) : BasicHttpEntityEnclosingRequest(new BasicRequestLine(method, uri, ver)) {
}
BasicHttpEntityEnclosingRequest::BasicHttpEntityEnclosingRequest(RequestLine *requestline) : BasicHttpRequest(requestline) {
}
HttpEntity* BasicHttpEntityEnclosingRequest::getEntity() { return entity; }
void BasicHttpEntityEnclosingRequest::setEntity(HttpEntity* e) { entity = e; }
bool BasicHttpEntityEnclosingRequest::expectContinue() {
    Header *expect = getFirstHeader(HTTP::EXPECT_DIRECTIVE);
    return ((expect != NULL) && (HTTP::EXPECT_CONTINUE == expect->getValue()));
}
