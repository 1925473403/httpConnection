#include "HttpException.h"
#ifndef HTTPMESSAGEPARSER_H
#define HTTPMESSAGEPARSER_H
class HttpMessageParser {
    public:
        virtual ~HttpMessageParser() { }
        virtual HttpMessage* parse() throw(IOException, HttpException) = 0;
};
#endif
