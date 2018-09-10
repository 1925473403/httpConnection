#ifndef REQUESTWRAPPER_H
#define REQUESTWRAPPER_H
class RequestWrapper : public AbstractHttpMessage, public HttpUriRequest {
    private:
        HttpRequest *original;
        URI *uri;
        std::string method;
        ProtocolVersion *version;
        int execCount;
    public:
        RequestWrapper(HttpRequest *request) ;
        void resetHeaders();
        std::string getMethod() const;
        void setMethod(std::string &m);
        ProtocolVersion *getVersion() const;
        void setVersion(ProtocolVersion *p);
        URI* getURI() const;
        void setURI(URI *uri);
        RequestLine* getRequestLine();
        void abort() throw (UnsupportedOperationException);
        bool isAborted();
        HttpRequest* getOriginal();
        bool isRepeatable();
        int getExecCount() const;
        void incrementExecCount();
};
#endif
