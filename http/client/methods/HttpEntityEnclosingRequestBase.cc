#include "HttpException.h"
#ifndef HTTPENTITYENCLOSINGREQUESTBASE_H
#include "HttpEntityEnclosingRequestBase.h"
#endif
HttpEntityEnclosingRequestBase::HttpEntityEnclosingRequestBase() { }

HttpEntity* HttpEntityEnclosingRequestBase::getEntity() {
    return entity;
}
void HttpEntityEnclosingRequestBase::setEntity(HttpEntity *e) {
    entity = e;
}
bool HttpEntityEnclosingRequestBase::expectContinue() {
    Header *header = getFirstHeader(HTTP::EXPECT_DIRECTIVE);
    return (header != NULL) && (equalsIgnoreCase(HTTP::EXPECT_CONTINUE, header->getValue()));
}
