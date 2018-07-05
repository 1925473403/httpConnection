#include "HttpException.h"
#ifndef HTTPRESPONSEPARSER_H
#define HTTPRESPONSEPARSER_H
class HttpResponseParser : public AbstractMessageParser {
    private:
        HttpResponseFactory *responseFactory;
        CharArrayBuffer lineBuf;
    public:
        HttpResponseParser(SessionInputBuffer *buffer, LineParser *parser, HttpResponseFactory *responseFactory, HttpParams *params);
        HttpMessage* parseHead(SessionInputBuffer* sessionBuffer) throw (IOException, HttpException, ParseException);
};
#endif
