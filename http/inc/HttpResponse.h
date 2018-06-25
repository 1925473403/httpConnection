#include "HttpException.h"
#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H
class HttpResponse : public HttpMessage {
    public:
    virtual ~HttpResponse() = 0;
    virtual StatusLine* getStatusLine() = 0;
    virtual void setStatusLine(StatusLine *statline) = 0;
    virtual void setStatusLine(ProtocolVersion *ver, int code) = 0;
    virtual void setStatusLine(ProtocolVersion *ver, int code, std::string reason) = 0;
    virtual void setStatusCode(int code) throw (IllegalStateException) = 0;
    virtual void setReasonPhrase(std::string *reason) throw (IllegalStateException) = 0;
    virtual HttpEntity* getEntity() = 0;
    virtual void setEntity(HttpEntity *entity) = 0;
    virtual Locale* getLocale() = 0;
    virtual void setLocale(Locale *loc) = 0;
};
#endif
