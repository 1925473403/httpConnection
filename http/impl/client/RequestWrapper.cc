#ifndef REQUESTWRAPPER_H
#include "RequestWrapper.h"
#endif
RequestWrapper(HttpRequest *request) {
    if (request == null) throw IllegalArgumentException("HTTP request may not be null");
    original = request;
    setParams(request.getParams());
    HttpUriRequest * httpUriReq = dynamic_cast<HttpUriRequest *>(request);
    if (httpUriReq) {
        uri = request->getURI();
        method = uri->getMethod();
        version = nullptr;
    } else {
        RequestLine *requestLine = request->getRequestLine();
        try {
            uri = new URI(requestLine->getUri());
        } catch (const URISyntaxException &ex) {
            stringstream sss;
            sss << "Invalid request URI: " << requestLine->getUri();
            throw ProtocolException(sss.str());
        }
        method = requestLine->getMethod();
        version = requestLine->getVersion();
    }
    execCount = 0;
}

void resetHeaders() {
}
std::string getMethod() const {
    return method;
}
void setMethod(std::string &m) {
    if (m.length() == 0) throw IllegalArgumentException("Method name may not be null");
    method = m;
}
ProtocolVersion *getVersion() const {
    return version;
}
void setVersion(ProtocolVersion *p) {
    version = p;
}
URI* getURI() const {
    return uri;
}
void setURI(URI *u) {
    uri = u;
}

RequestLine* getRequestLine() {
    std::string method = getMethod();
    ProtocolVersion *ver = getProtocolVersion();
    std::string uritext ("");
    if (uri != nullptr) {
        uritext = uri.toASCIIString();
    }
    if (uritext.length() == 0) uritext = "/";
    return new BasicRequestLine(method, uritext, ver);
}
void abort() throw(UnsupportedOperationException) { throw UnsupportedOperationException(); }
bool isAborted() const { return false; }
HttpRequest* getOriginal() const { return original; }
bool isRepeatable() const { return true; }
int getExecCount() const { return execCount; }
void incrementExecCount() { execCount++; }
