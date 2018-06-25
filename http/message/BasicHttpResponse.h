#ifndef BASICHTTPRESPONSE_H
#define BASICHTTPRESPONSE_H
class BasicHttpResponse : public AbstractHttpMessage , public HttpResponse {
    public:
        BasicHttpResponse(StatusLine *s, ReasonPhraseCatalog *e, Locale *l);
        BasicHttpResponse(StatusLine *s);
        BasicHttpResponse(ProtocolVersion *p, int code, std::string reason);
        ProtocolVersion* getProtocolVersion();
        StatusLine* getStatusLine();
        HttpEntity* getEntity();
        Locale* getLocale();
        void setStatusLine(StatusLine *s);
        void setStatusLine(ProtocolVersion *p, int code);
        void setStatusLine(ProtocolVersion *p, int code, std::string reason);
        void setStatusCode(int code);
        void setReasonPhrase(std::string reason);
        void setEntity(HttpEntity *e);
        void setLocale(Locale *l);
    private:
        StatusLine *statusline;
        HttpEntity *entity;
        ReasonPhraseCatalog *reasonCatalog;
        Locale *locale;
    protected:
        std::string getReason(int code);
};
#endif
