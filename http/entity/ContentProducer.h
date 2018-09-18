#include "HttpException.h"
#include "RefCount.h"
#include "OutputStream.h"
#ifndef CONTENTPRODUCER_H
#define CONTENTPRODUCER_H
class ContentProducer : public RefCount {
    public:
    virtual ~ContentProducer(){ }
    virtual void writeTo(OutputStream *outstream) throw(IOException) = 0;
};
#endif
