#include "HttpException.h"
#ifndef ABSTRACTMESSAGEWRITER_H
#include "AbstractMessageWriter.h"
#endif
AbstractMessageWriter::AbstractMessageWriter(SessionOutputBuffer *buffer, LineFormatter *formatter, HttpParams *params) : lineBuf(128) {
    if (buffer == NULL) throw IllegalArgumentException("Session input buffer may not be null");
    sessionBuffer = buffer;
    lineFormatter = ((formatter != NULL)? formatter : &(BasicLineFormatter::DEFAULT);
}
void AbstractMessageWriter::write(HttpMessage *message) throw (IOException, HttpException) {
    if (message == NULL) throw IllegalArgumentException("HTTP message may not be null");
    writeHeadLine(message);
    for (HeaderIterator *it = message->headerIterator(); it->hasNext(); ) {
        Header *header = reinterpret_cast<Header *>(it->next());
        sessionBuffer->writeLine(lineFormatter->formatHeader(&lineBuf, header));
    }
    lineBuf.clear();
    sessionBuffer->writeLine(&lineBuf);
}
