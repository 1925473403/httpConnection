#include "HttpException.h"
#ifndef HTTPRESPONSEWRITER_H
#define HTTPRESPONSEWRITER_H
class HttpResponseWriter : public AbstractMessageWriter {
    public:
        HttpResponseWriter(SessionOutputBuffer *buffer, LineFormatter *formatter, HttpParams *params);
        void writeHeadLine(HttpMessage *message) throw (IOException);
};
#endif
