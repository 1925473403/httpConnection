#include "HttpException.h"
#ifndef URLENCODEDFORMENTITY_H
#include "UrlEncodedFormEntity.h"
#endif
UrlEncodedFormEntity::UrlEncodedFormEntity(vector<NameValuePair *> &parameters, std::string encoding) throw (UnsupportedEncodingException) : StringEntity(URLEncodedUtils.format(parameters, encoding), encoding) {
    setContentType(URLEncodedUtils::CONTENT_TYPE);
}

UrlEncodedFormEntity::UrlEncodedFormEntity(vector<NameValuePair *> &parameters) throw (UnsupportedEncodingException) : StringEntity(URLEncodedUtils.format(parameters, HTTP::DEFAULT_CONTENT_CHARSET), HTTP::DEFAULT_CONTENT_CHARSET) {
    setContentType(URLEncodedUtils::CONTENT_TYPE);
}
