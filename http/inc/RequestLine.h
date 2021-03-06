#include "HttpException.h"
#include "RefCount.h"
#ifndef REQUESTLINE_H
#define REQUESTLINE_H
class RequestLine : public RefCount {
    public:
    virtual ~RequestLine() { }
    virtual ProtocolVersion* getProtocolVersion() = 0;
    virtual std::string getMethod() const = 0;
    virtual std::string getUri() const = 0;
};
#endif
