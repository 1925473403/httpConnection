#include "HttpException.h"
#ifndef HTTPPOST_H
#include "HttpPost.h"
#endif
std::string HttpPost::METHOD_NAME("POST");
HttpPost::HttpPost() : HttpEntityEnclosingRequestBase() {
}
HttpPost::HttpPost(std::string Uri):HttpEntityEnclosingRequestBase(){
    setURI(URI::create(Uri));
}
HttpPost::HttpPost(URI uri) {
    setURI(URI);
}
std::string HttpPost::getMethod() {
    return METHOD_NAME;
}
