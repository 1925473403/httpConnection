#include "AbstractMessageParser.h"
AbstractMessageParser::AbstractMessageParser(SessionInputBuffer *buffer, LineParser *parser, HttpParams *params) {
    if (buffer == NULL) throw IllegalArgumentException("Session input buffer may not be null");
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    sessionBuffer = buffer;
    maxHeaderCount = params.getIntParameter(CoreConnectionPNames::MAX_HEADER_COUNT, -1);
    maxLineLen = params.getIntParameter(CoreConnectionPNames::MAX_LINE_LENGTH, -1);
    lineParser = ((parser != null)? parser : &(BasicLineParser::DEFAULT);
}

AbstractMessageParser::parseHeaders(SessionInputBuffer *inbuffer, int maxHeaderCount, int maxLineLen, LineParser *parser, vector<Header*> &headers) throw(HttpException, IOException) {
    if (inbuffer == NULL) throw IllegalArgumentException("Session input buffer may not be null");
    if (parser == NULL) parser = &(BasicLineParser::DEFAULT);

    vector<CharArrayBuffer> headerLines;
    CharArrayBuffer current(64), previous(0);
    for (;;) {
        current.clear();
        int l = inbuffer.readLine(current);
        if (l == -1 || current.length() < 1) break;
        if ((current.charAt(0) == ' ' || current.charAt(0) == '\t') && (previous.length() > 0)) {
            int i = 0;
            while (i < current.length()) {
                char ch = current.charAt(i);
                if (ch != ' ' && ch != '\t') break;
                i++;
            }
            if (maxLineLen > 0 && previous.length() + 1 + current.length() - i > maxLineLen) throw IOException("Maximum line length limit exceeded");
            previous.append(' ');
            previous.append(current, i, current.length() - i);
        } else {
            headerLines.push_back(current);
            previous = current;
            current.clear();
        }
        if (maxHeaderCount > 0 && headerLines.size() >= maxHeaderCount) throw  IOException("Maximum header count exceeded");
    }
    headers.resize(headerLines.size(), 0);
    for (int i = 0; i < headerLines.size(); i++) {
        CharArrayBuffer buffer = headerLines[i];
        try {
            headers[i] = parser->parseHeader(buffer);
        } catch (const ParseException &ex) {
            throw ex;
        }
    }
    return ;
}

HttpMessage *AbstractMessageParser::parse() throw(IOException, HttpException) {
    HttpMessage *message = NULL;
    try {
        message = parseHead(sessionBuffer);
    } catch (ParseException &ex) {
        throw ex;
    }
    vector<Header *> headers;
    AbstractMessageParser::parseHeaders(sessionBuffer, maxHeaderCount, maxLineLen, lineParser, headers);
    message->setHeaders(headers);
    return message;
}
