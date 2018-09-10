#include "HttpException.h"
#ifndef SETCOOKIE2_H
#define SETCOOKIE2_H
class SetCookie2 : public SetCookie {
    public:
    virtual ~SetCookie2();
    virtual void setCommmentURL(std::string &) = 0;
    virtual void setPorts(vector<int> &) = 0;
    virtual void setDiscard(bool ) = 0;
};
#endif
