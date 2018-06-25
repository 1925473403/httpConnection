#include "ProtocolVersion.h"
#include "HttpVersion.h"
std::string HttpVersion::HTTP = std::string("HTTP");
HttpVersion *HttpVersion::HTTP_1_0 = new HttpVersion(1, 0);
HttpVersion *HttpVersion::HTTP_1_1 = new HttpVersion(1, 1);
HttpVersion *HttpVersion::HTTP_0_9 = new HttpVersion(0, 9);
HttpVersion::HttpVersion(int maj, int min):ProtocolVersion(HTTP, maj, min) { }
HttpVersion::~HttpVersion() { }
void HttpVersion::unref() {
    if (this == HTTP_1_0 || this == HTTP_1_1 || this == HTTP_0_9) return;
    delete this;
}
HttpVersion::HttpVersion(const HttpVersion& rhs):ProtocolVersion(rhs) {
}
HttpVersion& HttpVersion::operator=(const HttpVersion &rhs) {
    ProtocolVersion::operator=(rhs);
    return *this;
}
ProtocolVersion* HttpVersion::forVersion(int ma, int mi) {
    if (maj == ma && min == mi) return this;
    if (maj == 1) {
        if (min == 0) return HTTP_1_0;
        if (min == 1) return HTTP_1_1;
    }
    if ((maj == 0) && (min == 9)) return HTTP_0_9;
    return new HttpVersion(ma, mi);
}
