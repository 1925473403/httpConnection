#include "HttpException.h"
#ifndef HTTPGET_H
#include "HttpGet.h"
#endif
std::string HttpGet::METHOD_NAME("GET");
HttpGet::HttpGet() : HttpEntityEnclosingRequestBase() {
}
HttpGet::HttpGet(std::string Uri):HttpEntityEnclosingRequestBase(){
    setURI(Uri);
}
HttpGet::HttpGet(URI uri) {
    setURI(URI);
}
std::string HttpGet::getMethod() {
    return METHOD_NAME;
}
