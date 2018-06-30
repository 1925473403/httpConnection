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
        virtual HttpMessage* parseHead(SessionInputBuffer*) throw(IOException, HttpException, ParseException) = 0;
    public:
        AbstractMessageParser(SessionInputBuffer *, LineParser*, HttpParams*);
        static void parseHeaders(SessionInputBuffer *, int, int LineParser*, vector<Header *> &headers) throw(HttpException, IOException);
        virtual HttpMessage* parse() throw(IOException, HttpException) = 0;
};
#endif
