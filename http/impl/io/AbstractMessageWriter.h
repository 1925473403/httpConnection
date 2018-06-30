#include "HttpException.h"
#ifndef ABSTRACTMESSAGEWRITER_H
#define ABSTRACTMESSAGEWRITER_H
class AbstractMessageWriter : public HttpMessageWriter {
    protected:
        SessionOutputBuffer *sessionBuffer;
        CharArrayBuffer lineBuf;
        LineFormatter *lineFormatter;
    public:
        AbstractMessageWriter(SessionOutputBuffer *buffer, LineFormatter *formatter, HttpParams *params);
        virtual ~AbstractMessageWriter() { }
        virtual void writeHeadLine(HttpMessage *message) throw (IOException) = 0;
        virtual void write(HttpMessage *message) throw (IOException, HttpException) = 0;
};
#endif
