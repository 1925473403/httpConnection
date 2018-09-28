#include "HttpException.h"
#ifndef BASICHTTPPROCESSOR_H
#define BASICHTTPPROCESSOR_H
class BasicHttpProcessor : public HttpProcessor, public HttpRequestInterceptorList, public HttpResponseInterceptorList {
    public:
    void addRequestInterceptor(HttpRequestInterceptor *itcp);
    void addRequestInterceptor(HttpRequestInterceptor *itcp, int index);
    void addResponseInterceptor(HttpResponseInterceptor *itcp, int index);
//    void removeRequestInterceptorByClass(
//    void removeResponseInterceptorByClass(
    void addInterceptor(HttpRequestInterceptor *);
    void addInterceptor(HttpRequestInterceptor *);
    int getRequestInterceptorCount();
    HttpRequestInterceptor* getRequestInterceptor(int index);
    void clearRequestInterceptors();
    void addResponseInterceptor(HttpResponseInterceptor *itcp);
    void addInterceptor(HttpResponseInterceptor *);
    void addInterceptor(HttpResponseInterceptor*, int);
    protected:
    vector<HttpResponseInterceptorList *> responseInterceptors;
    vector<HttpRequestInterceptorList *> requestInterceptors;
};
#endif
