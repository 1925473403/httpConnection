#include "HttpException.h"
#ifndef HTTPMESSAGE_H
#define HTTPMESSAGE_H
class HttpMessage {
    public:
    virtual ~HttpMessage() { }
    virtual ProtocolVersion* getProtocolVersion() = 0;
    virtual bool containsHeader(std::string name) = 0;
    virtual void getHeaders(std::string name, vector<Header*> &) = 0;
    virtual Header* getFirstHeader(std::string name) = 0;
    virtual Header* getLastHeader(std::string name) = 0;
    virtual void getAllHeaders(vector<Header*> &) = 0;
    virtual void addHeader(Header* header) = 0;
    virtual void addHeader(std::string name, std::string value) = 0;
    virtual void setHeader(Header* header) = 0;
    virtual void setHeader(std::string name, std::string value) = 0;
    virtual void setHeaders(vector<Header*> &headers) = 0;
    virtual void removeHeader(Header* header) = 0;
    virtual void removeHeaders(std::string name) = 0;
    virtual HeaderIterator* headerIterator() = 0;
    virtual HeaderIterator* headerIterator(std::string name) = 0;
    virtual HttpParams* getParams() = 0;
    virtual void setParams(HttpParams* params) = 0;
};
#endif
