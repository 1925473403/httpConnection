#include "HttpException.h"
#include "CharArrayBuffer.h"
#include "ProtocolVersion.h"
#include "Header.h"
#include "HeaderIterator.h"
#include "HttpParams.h"
#include "AbstractHttpParams.h"
#include "BasicHttpParams.h"
#include "HttpMessage.h"
#include "HttpHost.h"
#include "HttpVersion.h"
#include "HeaderGroup.h"
#include "BasicHeader.h"
#ifndef ABSTRACTHTTPMESSAGE_H
#include "AbstractHttpMessage.h"
#endif
AbstractHttpMessage::AbstractHttpMessage(HttpParams *p) {
    headergroup = new HeaderGroup();
    params = p;
    if (params) params->ref();
}

AbstractHttpMessage::~AbstractHttpMessage() {
    if (headergroup) headergroup->unref();
    if (params) params->unref();
}

AbstractHttpMessage::AbstractHttpMessage() : params(NULL) {
    headergroup = new HeaderGroup();
}

bool AbstractHttpMessage::containsHeader(std::string name) {
    return headergroup->containsHeader(name);
}

void AbstractHttpMessage::getHeaders(std::string name, vector<Header *> &res) {
    headergroup->getHeaders(name, res);
}

Header* AbstractHttpMessage::getFirstHeader(std::string name) {
    return headergroup->getFirstHeader(name);
}

Header* AbstractHttpMessage::getLastHeader(std::string name) {
    return headergroup->getLastHeader(name);
}

void AbstractHttpMessage::getAllHeaders(vector<Header*> &res) {
    headergroup->getAllHeaders(res);
}

void AbstractHttpMessage::addHeader(Header* header) {
    headergroup->addHeader(header);
}

void AbstractHttpMessage::addHeader(std::string name, std::string value) {
    if (name.length() == 0) throw IllegalArgumentException("Header name may not be null");
    headergroup->addHeader(new BasicHeader(name, value));
}

void AbstractHttpMessage::setHeader(Header* header) {
    headergroup->updateHeader(header);
}

void AbstractHttpMessage::setHeader(std::string name, std::string value) {
    if (name.length() == 0) throw IllegalArgumentException("Header name may not be null");
    headergroup->updateHeader(new BasicHeader(name, value));
}

void AbstractHttpMessage::setHeaders(vector<Header*> &headers) {
    headergroup->setHeaders(headers);
}

void AbstractHttpMessage::removeHeader(Header* header) {
    headergroup->removeHeader(header);
}

void AbstractHttpMessage::removeHeaders(std::string name) {
    if (name.length() == 0) return;
}

HeaderIterator* AbstractHttpMessage::headerIterator() {
    return headergroup->iterator();
}

HeaderIterator* AbstractHttpMessage::headerIterator(std::string name) {
    return headergroup->iterator(name);
}

HttpParams* AbstractHttpMessage::getParams()  {
    if (params == NULL) params = new BasicHttpParams();
    params->ref();
    return params;
}

void AbstractHttpMessage::setParams(HttpParams* p) {
    if (p = NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params = p;
    if (params) params->ref();
}
