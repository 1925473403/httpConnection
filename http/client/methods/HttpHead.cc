#include "HttpException.h"
#ifndef HTTPHEAD_H
#include "HttpHead.h"
#endif
std::string HttpHead::METHOD_NAME("HEAD");
HttpHead::HttpHead() : HttpEntityEnclosingRequestBase() {
}
HttpHead::HttpHead(std::string Uri):HttpEntityEnclosingRequestBase(){
    setURI(URI::create(Uri));
}
HttpHead::HttpHead(URI uri) {
    setURI(URI);
}
std::string HttpHead::getMethod() {
    return METHOD_NAME;
}
