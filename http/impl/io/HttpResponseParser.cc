#include "HttpException.h"
#include "HttpMessage.h"
#include "HttpResponseFactory.h"
#include "StatusLine.h"
#include "SessionInputBuffer.h"
#include "LineParser.h"
#include "ParserCursor.h"
#include "HttpParams.h"
#include "CharArrayBuffer.h"
#ifndef HTTPRESPONSEPARSER_H
#include "HttpResponseParser.h"
#endif
HttpResponseParser::HttpResponseParser(SessionInputBuffer *buffer, LineParser *parser, HttpResponseFactory *responseFact, HttpParams *params) :
    AbstractMessageParser(buffer, parser, params), lineBuf(128) {
        if (responseFact == NULL) throw IllegalArgumentException("Response factory may not be null");
        responseFactory = responseFact;
}
HttpMessage* HttpResponseParser::parseHead(SessionInputBuffer* sessionBuffer) throw (IOException, HttpException, ParseException) {
    lineBuf.clear();
    int i = sessionBuffer->readLine(lineBuf);
    if (i == -1) throw NoHttpResponseException("The target server failed to respond");
    ParserCursor cursor (0, lineBuf.length());
    StatusLine *statusline = lineParser->parseStatusLine(lineBuf, &cursor);
    HttpMessage *res = responseFactory->newHttpResponse(statusline, null);
    return res;
}
