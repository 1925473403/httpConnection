#include "HttpException.h"
#ifndef ABORTABLEHTTPREQUEST_H
#define ABORTABLEHTTPREQUEST_H
class AbortableHttpRequest {
    public:
    virtual ~AbortableHttpRequest() { }
    virtual void setConnectionRequest(ClientConnectionRequest* connRequest) throw (IOException) = 0;
    virtual void setReleaseTrigger(ConnectionReleaseTrigger* releaseTrigger) throw (IOException) = 0;
    virtual void abort() = 0;
};
#endif
