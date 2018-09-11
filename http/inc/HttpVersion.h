#ifndef HTTPVERSION_H
#define HTTPVERSION_H
class HttpVersion : public ProtocolVersion {
    public:
        ~HttpVersion();
        static HttpVersion *HTTP_1_0;
        static HttpVersion *HTTP_1_1;
        static HttpVersion *HTTP_0_9;
        static std::string HTTP;
        HttpVersion(int maj, int min);
        ProtocolVersion* forVersion(int ma, int mi) ;
        HttpVersion(const HttpVersion&);
        HttpVersion& operator=(const HttpVersion&);
};
#endif
