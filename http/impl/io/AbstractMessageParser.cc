#include "AbstractMessageParser.h"
AbstractMessageParser::AbstractMessageParser(SessionInputBuffer *buffer, LineParser *parser, HttpParams *params) {
    if (buffer == NULL) throw IllegalArgumentException("Session input buffer may not be null");
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    sessionBuffer = buffer;
    maxHeaderCount = params.getIntParameter(CoreConnectionPNames::MAX_HEADER_COUNT, -1);
    maxLineLen = params.getIntParameter(CoreConnectionPNames::MAX_LINE_LENGTH, -1);
    lineParser = ((parser != null)? parser : BasicLineParser::DEFAULT;
}

std::vector<Header> AbstractMessageParser::parseHeaders(SessionInputBuffer *inbuffer, int maxHeaderCount, int maxLineLen, LineParser *parser) throws HttpException, IOException {
    if (inbuffer == NULL) throw IllegalArgumentException("Session input buffer may not be null");
    if (parser == NULL) parser = BasicLineParser::DEFAULT;

    CharArrayBuffer current(64), previous;
    for (;;) {
        current.clear();
        int l = inbuffer.readLine(current);
        if (l == -1 || current.length() < 1) break;
    }
}
