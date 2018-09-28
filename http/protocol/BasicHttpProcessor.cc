#include "HttpException.h"
#ifndef BASICHTTPPROCESSOR_H
#include "BasicHttpProcessor.h"
#endif
void BasicHttpProcessor::addRequestInterceptor(HttpRequestInterceptor *itcp) {
}
void BasicHttpProcessor::addRequestInterceptor(HttpRequestInterceptor *itcp, int index) {
}
void BasicHttpProcessor::addResponseInterceptor(HttpResponseInterceptor *itcp, int index) {
}
//    void removeRequestInterceptorByClass(
//    void removeResponseInterceptorByClass(
void BasicHttpProcessor::addInterceptor(HttpRequestInterceptor *) {
}
void BasicHttpProcessor::addInterceptor(HttpRequestInterceptor *) {
}
int BasicHttpProcessor::getRequestInterceptorCount() {
}
HttpRequestInterceptor* BasicHttpProcessor::getRequestInterceptor(int index) {
}
void BasicHttpProcessor::clearRequestInterceptors() {
}
void BasicHttpProcessor::addResponseInterceptor(HttpResponseInterceptor *itcp) {
}
void BasicHttpProcessor::addInterceptor(HttpResponseInterceptor *) {
}
void BasicHttpProcessor::addInterceptor(HttpResponseInterceptor*, int) {
}
