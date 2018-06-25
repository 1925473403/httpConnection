#include "HttpException.h"
#ifndef DEFAULTEDHTTPCONTEXT_H
#define DEFAULTEDHTTPCONTEXT_H
class DefaultedHttpContext : public HttpContext {
    private:
        HttpContext* local;
        HttpContext *defaults;
    public:
        DefaultedHttpContext(HttpContext *l, HttpContext *d) ;
        ~DefaultedHttpContext() { }
        ValueBase *getAttribute(std::string id) ;
        ValueBase *removeAttribute(std::string id) ;
        HttpContext *getDefaults() ;
        void setAttribute(std::string id, ValueBase *obj) ;
}; 
#endif
