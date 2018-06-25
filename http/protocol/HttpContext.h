#ifndef HTTPCONTEXT_H
#define HTTPCONTEXT_H
class HttpContext {
    public:
        static std::string RESERVED_PREFIX;
        virtual HttpContext* getAttribute(std::string &id) = 0;
        virtual void setAttribute(std::string &id, HttpContext *obj) = 0;
        virtual HttpContext* removeAttribute(std::string &id) = 0;
};
#endif
