#include "HttpException.h"
#ifndef HTTPREQUESTINTERCEPTORLIST_H
#define HTTPREQUESTINTERCEPTORLIST_H
class HttpRequestInterceptorList : public virtual RefCount {
    public:
    virtual ~HttpRequestInterceptorList() { }
    virtual void addRequestInterceptor(HttpRequestInterceptor* itcp) = 0;
    virtual void void addRequestInterceptor(HttpRequestInterceptor* itcp, int index) = 0;
    virtual int getRequestInterceptorCount() = 0;
    virtual HttpRequestInterceptor* getRequestInterceptor(int index) = 0;
    virtual void clearRequestInterceptors() = 0;
    virtual void setInterceptors(vector<HttpRequestInterceptor *> itcps) = 0;
};
#endif
