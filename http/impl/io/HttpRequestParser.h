#include "HttpException.h"
#ifndef HTTPREQUESTPARSER_H
#define HTTPREQUESTPARSER_H
class HttpRequestParser : public AbstractMessageParser {
    private:
        HttpRequestFactory *requestFactory;
        CharArrayBuffer lineBuf;
    protected:
    public:
        HttpRequestParser(SessionInputBuffer *buffer, LineParser *parser, HttpRequestFactory *factory, HttpParams *params);
        HttpMessage* parserHead(SessionInputBuffer *buffer) throw( IOException, HttpException, ParseException);
};
#endif
