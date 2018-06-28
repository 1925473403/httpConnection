#include "HttpException.h"
#ifndef USERTOKENHANDLER_H
#define USERTOKENHANDLER_H
class UserTokenHandler {
    public:
        virtual ~UserTokenHandler() { }
        ValueBase *getUserToken(HttpContext *context);
};
#endif
