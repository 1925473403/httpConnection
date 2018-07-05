#include "HttpException.h"
#ifndef HTTPMESSAGEWRITER_H
#define HTTPMESSAGEWRITER_H
class HttpMessageWriter {
    public:
        virtual ~HttpMessageWriter() { }
        virtual void write(HttpMessage *message) throw(IOException, HttpException) = 0;
};
#endif
