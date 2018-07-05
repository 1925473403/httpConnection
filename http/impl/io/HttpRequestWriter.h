#include "HttpException.h"
#ifndef HTTPREQUESTWRITER_H
#define HTTPREQUESTWRITER_H
class HttpRequestWriter : public AbstractMessageWriter {
    public:
        HttpRequestWriter(SessionOutputBuffer *buffer, LineFormatter *formatter, HttpParams *params);
        void writeHeadLine(HttpMessage *message) throw (IOException);
};
#endif
