#include "HttpException.h"
#ifndef HTTPTRACE_H
#include "HttpTrace.h"
#endif
std::string HttpTrace::METHOD_NAME("TRACE");
HttpTrace::HttpTrace() : HttpEntityEnclosingRequestBase() {
}
HttpTrace::HttpTrace(std::string Uri):HttpEntityEnclosingRequestBase(){
    setURI(URI::create(Uri));
}
HttpTrace::HttpTrace(URI uri) {
    setURI(URI);
}
std::string HttpTrace::getMethod() {
    return METHOD_NAME;
}
