#include "HttpException.h"
#ifndef HTTPDELETE_H
#include "HttpDelete.h"
#endif
std::string HttpDelete::METHOD_NAME("DELETE");
HttpDelete::HttpDelete() : HttpEntityEnclosingRequestBase() {
}
HttpDelete::HttpDelete(std::string Uri):HttpEntityEnclosingRequestBase(){
    setURI(URI::create(Uri));
}
HttpDelete::HttpDelete(URI uri) {
    setURI(URI);
}
std::string HttpDelete::getMethod() {
    return METHOD_NAME;
}
