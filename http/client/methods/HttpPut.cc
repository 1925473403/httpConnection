#include "HttpException.h"
#ifndef HTTPPUT_H
#include "HttpPut.h"
#endif
std::string HttpPut::METHOD_NAME("PUT");
HttpPut::HttpPut() : HttpEntityEnclosingRequestBase() {
}
HttpPut::HttpPut(std::string Uri):HttpEntityEnclosingRequestBase(){
    setURI(URI::create(Uri));
}
HttpPut::HttpPut(URI uri) {
    setURI(URI);
}
std::string HttpPut::getMethod() {
    return METHOD_NAME;
}
