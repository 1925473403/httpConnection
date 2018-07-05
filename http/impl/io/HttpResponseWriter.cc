#include "HttpException.h"
#ifndef HTTPRESPONSEWRITER_H
#include "HttpResponseWriter.h"
#endif
HttpResponseWriter(SessionOutputBuffer *buffer, LineFormatter *formatter, HttpParams *params) : AbstractMessageWriter(buffer, formatter, params) {
}
void writeHeadLine(HttpMessage *message) throw (IOException) {
    HttpResponse *response = dynamic_cast<HttpResponse *>(message);
    CharArrayBuffer buffer = lineFormatter->formatStatusLine(lineBuf, response->getStatusLine());
    sessionBuffer->writeLine(buffer);
}
