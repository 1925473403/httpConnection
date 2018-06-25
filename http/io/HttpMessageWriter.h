#include "HttpException.h"
#ifndef HTTPMESSAGEWRITER_H
#define HTTPMESSAGEWRITER_H
class HttpMessageWriter {
    public:
        void write(HttpMessage *message) throws IOException, HttpException = 0;
};
#endif
