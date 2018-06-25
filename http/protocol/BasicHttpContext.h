#include "HttpException.h"
#ifndef BASICHTTPCONTEXT_H
#define BASICHTTPCONTEXT_H
class BasicHttpContext : public HttpContext {
    private:
        HttpContext *parentContext;
        std::unordered_map<std::string, ValueBase*> map;
    public:
        BasicHttpContext();
        BasicHttpContext(HttpContext *obj) ;
        ~BasicHttpContext() { }
        ValueBase* getAttribute(std::string id) ;
        void setAttribute(std::string id, ValueBase *obj) ;
        ValueBase *removeAttribute(std::string id) ;
};
#endif
