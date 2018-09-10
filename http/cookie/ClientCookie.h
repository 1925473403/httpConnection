#include "HttpException.h"
#ifndef CLIENTCOOKIE_H
#define CLIENTCOOKIE_H
class ClientCookie : public Cookie {
    public:
        static std::string VERSION_ATTR;
        static std::string PATH_ATTR;
        static std::string DOMAIN_ATTR;
        static std::string MAX_AGE_ATTR;
        static std::string SECURE_ATTR ;
        static std::string COMMENT_ATTR;
        static std::string EXPIRES_ATTR;
        static std::string PORT_ATTR;
        static std::string COMMENTURL_ATTR;
        static std::string DISCARD_ATTR;
        virtual std::string getAttribute(std::string name) = 0;
        virtual bool containsAttribute(std::string name) = 0;
        virtual ~ClientCookie();
};
#endif
