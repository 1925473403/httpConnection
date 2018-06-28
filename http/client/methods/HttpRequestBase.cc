#include "HttpException.h"
#ifndef HTTPREQUESTBASE_H
#include "HttpRequestBase.h"
#endif
HttpRequestBase::HttpRequestBase() {
}

ProtocolVersion* HttpRequestBase::getProtocolVersion() {
    return HttpProtocolParams::getVersion(getParams());
}

URI HttpRequestBase::getURI() { return uri; }
RequestLine* HttpRequestBase::getRequestLine() {
    std::string method = getMethod();
    ProtocolVersion* ver = getProtocolVersion();
    URI uri = getURI();
    std::string uritext = "";
    if (uri != NULL) uritext = uri->toASCIIString();
    if (uritext.length() == 0) uritext = "/";
    return new BasicRequestLine(method, uritext, ver);
}
void HttpRequestBase::setURI(URI u) {
    uri = u;
}
void HttpRequestBase::setConnectionRequest(ClientConnectionRequest* connReq) {
    {
        Lock l(abortLock);
        try {
            if (aborted) throw IOException("Request already aborted");
            releaseTrigger = NULL;
            connRequest = connReq;
        } catch (...) { }
    }
}
void HttpRequestBase::setReleaseTrigger(ConnectionReleaseTrigger* releaseTrig) {
    {
        Lock l(abortLock);
        try {
            if (aborted) throw IOException("Request already aborted");
            connRequest = NULL;
            releaseTrigger = releaseTrig;
        } catch(..) { }
    }
}
void HttpRequestBase::abort() {
    ClientConnectionRequest* localRequest = NULL;
    ConnectionReleaseTrigger* localTrigger = NULL;
    {
        Lock l(abortLock);
        try {
            if (aborted) return;
            aborted = true;
            localRequest = connRequest;
            localTrigger = releaseTrigger;
        } catch (...) {
        }
    }
    if (localRequest) {
        localRequest->abortRequest();
    }
    if (localTrigger) {
        try {
            localTrigger->abortConnection();
        } catch (const IOException &ex) { }
    }
}
bool HttpRequestBase::isAborted() { return aborted; }
