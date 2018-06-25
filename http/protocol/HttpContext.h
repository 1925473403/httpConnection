#include "HttpException.h"
#ifndef HTTPCONTEXT_H
#define HTTPCONTEXT_H
class HttpContext {
    public:
        static std::string RESERVED_PREFIX;
        virtual ~HttpContext() { }
        virtual ValueBase* getAttribute(std::string id) = 0;
        virtual void setAttribute(std::string id, ValueBase *obj) = 0;
        virtual ValueBase* removeAttribute(std::string id) = 0;
};
#endif
