#include "HttpException.h"
#ifndef HTTPREQUESTWRITER_H
#include "HttpRequestWriter.h"
#endif
HttpRequestWriter(SessionOutputBuffer *buffer, LineFormatter *formatter, HttpParams *params) : AbstractMessageWriter(buffer, formatter, params) {
}
void writeHeadLine(HttpMessage *message) throw (IOException) {
    HttpRequest *response = dynamic_cast<HttpRequest *>(message);
    CharArrayBuffer buffer = lineFormatter->formatRequestLine(lineBuf, response->getRequestLine());
    sessionBuffer->writeLine(buffer);
}
