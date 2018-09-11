#include "HttpException.h"
#include "RefCount.h"
#ifndef STATUSLINE_H
#define STATUSLINE_H
class StatusLine : public RefCount {
    public:
    virtual ~StatusLine() { }
    virtual ProtocolVersion* getProtocolVersion() = 0;
    virtual int getStatusCode() = 0;
    virtual std::string getReasonPhrase() = 0;
};
#endif
