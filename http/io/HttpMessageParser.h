#include "HttpException.h"
#ifndef HTTPMESSAGEPARSER_H
#define HTTPMESSAGEPARSER_H
class HttpMessageParser {
    public:
        HttpMessage* parse() throws IOException, HttpException = 0;
};
#endif
