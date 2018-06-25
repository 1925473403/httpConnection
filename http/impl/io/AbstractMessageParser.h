#include "HttpException.h"
#ifndef ABSTRACTMESSAGEPARSER_H
#define ABSTRACTMESSAGEPARSER_H
class AbstractMessageParser : public HttpMessageParser {
    private:
        SessionInputBuffer *sessionBuffer;
        int maxHeaderCount;
        int maxLineLen;
        LineParser *lineParser;
    protected:
        HttpMessage* parseHead(SessionInputBuffer*) throws IOException, HttpException, ParseException = 0;
    public:
        AbstractMessageParser(SessionInputBuffer *, LineParser*, HttpParams*);
        vector<Header> parseHeaders(SessionInputBuffer *, int, int LineParser*) throws HttpException, IOException;
        HttpMessage* parse() throws IOException, HttpException;
};
#endif
