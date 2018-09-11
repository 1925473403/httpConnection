#include "HttpException.h"
#ifndef BASICREQUESTLINE_H
#define BASICREQUESTLINE_H
class BasicRequestLine : public RequestLine {
    private:
    ProtocolVersion *protoversion;
    std::string method;
    std::string uri;
    public:
    BasicRequestLine(std::string m, std::string u, ProtocolVersion *version);
    virtual ~BasicRequestLine();
    std::string getMethod() const { return method; }
    ProtocolVersion* getProtocolVersion() { return protoversion; }
    std::string getUri() const { return uri; }
    std::string toString();
};
#endif
