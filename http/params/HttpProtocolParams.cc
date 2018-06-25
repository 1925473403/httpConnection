#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include "HttpParams.h"
#include "CoreProtocolPNames.h"
#include "ProtocolVersion.h"
#include "HttpVersion.h"
#include "HttpProtocolParams.h"
#include "HTTP.h"
std::string HttpProtocolParams::getHttpElementCharset(HttpParams *params) {
    std::string charset = "";
    ValueBase *v = params->getParameter(CoreProtocolPNames::HTTP_ELEMENT_CHARSET);
    if (v != NULL) {
        Value<std::string> *vObj = dynamic_cast<Value<std::string> *> (v);
        if (vObj != NULL) charset = vObj->value();
    }
    if (charset.length() == 0) charset = HTTP::DEFAULT_PROTOCOL_CHARSET;
    return charset;
}
void HttpProtocolParams::setHttpElementCharset(HttpParams *params,  std::string &charset) {
    params->setParameter(CoreProtocolPNames::HTTP_ELEMENT_CHARSET, new Value<std::string>(charset));
}
std::string HttpProtocolParams::getContentCharset(HttpParams *params) {
    std::string charset ;
    ValueBase *v = params->getParameter(CoreProtocolPNames::HTTP_CONTENT_CHARSET);
    if (v != NULL) {
        Value<std::string> *vObj = dynamic_cast<Value<std::string> *> (v);
        if (vObj != NULL) charset = vObj->value();
    }
    if (charset.length() == 0) charset = HTTP::DEFAULT_CONTENT_CHARSET;
    return charset;
}
void HttpProtocolParams::setContentCharset(HttpParams *params,  std::string &charset) {
    params->setParameter(CoreProtocolPNames::HTTP_CONTENT_CHARSET, new Value<std::string>(charset));
}
ProtocolVersion* HttpProtocolParams::getVersion(HttpParams *params) {
    ProtocolVersion *p = NULL;
    ValueBase *v = params->getParameter(CoreProtocolPNames::PROTOCOL_VERSION);
    if (v != NULL) {
        Value<ProtocolVersion *> *vObj = dynamic_cast<Value <ProtocolVersion *> *> (v);
        if (vObj != NULL) p = vObj->value();
    }
    if (p == NULL) return (HttpVersion::HTTP_1_1);
    return p;
}
void HttpProtocolParams::setVersion(HttpParams *params,  ProtocolVersion* version) {
    params->setParameter(CoreProtocolPNames::PROTOCOL_VERSION, new Value<ProtocolVersion*>(version));
}
std::string HttpProtocolParams::getUserAgent(HttpParams *params) {
    std::string useragent = "";
    ValueBase *v = params->getParameter(CoreProtocolPNames::USER_AGENT);
    if (v != NULL) {
        Value<std::string> *vObj = dynamic_cast<Value<std::string> *> (v);
        if (vObj != NULL) useragent = vObj->value();
    }
    return useragent;
}
void HttpProtocolParams::setUserAgent(HttpParams *params,  std::string &useragent) {
    params->setParameter(CoreProtocolPNames::USER_AGENT, new Value<std::string>(useragent));
}
bool HttpProtocolParams::useExpectContinue(HttpParams *params) {
    return params->getBooleanParameter(CoreProtocolPNames::USE_EXPECT_CONTINUE, false);
}
void HttpProtocolParams::setUseExpectContinue(HttpParams *params,  bool b) {
    params->setBooleanParameter(CoreProtocolPNames::USE_EXPECT_CONTINUE, b);
}
