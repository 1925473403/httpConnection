#include "HttpException.h"
#ifndef ABSTRACTHTTPENTITY_H
#define ABSTRACTHTTPENTITY_H
class AbstractHttpEntity : public HttpEntity {
    protected:
    Header *contentType;
    Header *contentEncoding;
    bool chunked;
    public:
    AbstractHttpEntity();
    virtual ~AbstractHttpEntity() ;
    Header* getContentType();
    Header* getContentEncoding();
    bool isChunked();
    void setContentType(Header *h);
    void setContentType(std::string &s);
    void setContentEncoding(Header *h);
    void setContentEncoding(std::string &s);
    void setChunked(bool b);
    void consumeContent() throw (IOException);
};
#endif
