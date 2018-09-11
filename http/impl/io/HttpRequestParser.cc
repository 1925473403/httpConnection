#include "HttpException.h"
#ifndef HTTPREQUESTPARSER_H
#include "HttpRequestParser.h"
HttpRequestParser::HttpRequestParser(SessionInputBuffer *buffer, LineParser *parser, HttpRequestFactory *factory, HttpParams *params) : AbstractMessageParser(buffer, parser, params), lineBuf(128) {
    if (factory == NULL) throw IllegalArgumentException("Request factory may not be null");
    requestFactory = factory;
}
HttpMessage* HttpRequestParser::parseHead(SessionInputBuffer *buffer) throw( IOException, HttpException, ParseException) {
    lineBuf.clear();
    int i = sessionBuffer->readLine(lineBuf);
    if (i == -1) throw ConnectionClosedException("Client closed connection");
    ParserCursor cursor(0, this->lineBuf.length());
    RequestLine *requestline = lineParser->parseRequestLine(lineBuf, &cursor);
    HttpMessage *res = requestFactory->newHttpRequest(requestline);
    return res;
}
#endif
