#include "HttpException.h"
#include "RefCount.h"
#ifndef HTTPDATEGENERATOR_H
#define HTTPDATEGENERATOR_H
class HttpDateGenerator : public RefCount {
    long dateAsLong;
    std::string dateAsText;
    public:
    HttpDateGenerator();
    std::string getCurrentDate();
};
#endif
