#include "HttpException.h"
#include "RefCount.h"
#ifndef HTTPRESPONSEINTERCEPTORLIST_H
#define HTTPRESPONSEINTERCEPTORLIST_H
class HttpResponseInterceptorList : public RefCount {
    public:
    virtual ~HttpResponseInterceptorList() { }
    virtual void addResponseInterceptor(HttpResponseInterceptor* itcp) = 0;
    virtual void void addResponseInterceptor(HttpResponseInterceptor* itcp, int index) = 0;
    virtual int getResponseInterceptorCount() = 0;
    virtual HttpResponseInterceptor* getResponseInterceptor(int index) = 0;
    virtual void clearResponseInterceptors() = 0;
    virtual void setInterceptors(vector<HttpResponseInterceptor *> itcps) = 0;
};
#endif
