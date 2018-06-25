#include "HttpException.h"
#ifndef BASICSTATUSLINE_H
#define BASICSTATUSLINE_H
class BasicStatusLine : public StatusLine {
    private:
        ProtocolVersion *protoVersion;
        int statusCode;
        std::string reasonPhrase;
    public:
        BasicStatusLine(ProtocolVersion *version, int sc, std::string r);
        int getStatusCode();
        ProtocolVersion *getProtocolVersion();
        std::string getReasonPhrase();
        std::string toString();
};
#endif
