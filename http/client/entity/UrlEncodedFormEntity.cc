#include "HttpException.h"
#include "Value.h"
#include "NameValuePair.h"
#include "HeaderElement.h"
#include "Header.h"
#include "HTTP.h"
#include "InputStream.h"
#include "ByteArrayInputStream.h"
#include "OutputStream.h"
#include "HttpEntity.h"
#include "BasicHeader.h"
#include "AbstractHttpEntity.h"
#include "ByteArrayInputStream.h"
#include "StringEntity.h"
#ifndef URLENCODEDFORMENTITY_H
#include "UrlEncodedFormEntity.h"
#endif
UrlEncodedFormEntity::UrlEncodedFormEntity(vector<NameValuePair *> &parameters, std::string encoding) : StringEntity(URLEncodedUtils.format(parameters, encoding), encoding) {
    setContentType(URLEncodedUtils::CONTENT_TYPE);
}

UrlEncodedFormEntity::UrlEncodedFormEntity(vector<NameValuePair *> &parameters) : StringEntity(URLEncodedUtils.format(parameters, HTTP::DEFAULT_CONTENT_CHARSET), HTTP::DEFAULT_CONTENT_CHARSET) {
    setContentType(URLEncodedUtils::CONTENT_TYPE);
}
