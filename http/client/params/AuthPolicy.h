#include "HttpException.h"
#ifndef AUTHPOLICY_H
#define AUTHPOLICY_H
class AuthPolicy {
    private:
        AuthPolicy() { }
    public:
        static std::string NTLM;
        static std::string DIGEST;
        static std::string BASIC;
};
#endif
