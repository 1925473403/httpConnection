#include "HttpException.h"
#ifndef ABSTRACTHTTPMESSAGE_H
#define ABSTRACTHTTPMESSAGE_H
class AbstractHttpMessage : virtual public HttpMessage {
    protected:
        HeaderGroup *headergroup;
        HttpParams *params;
        AbstractHttpMessage(HttpParams *params);
        AbstractHttpMessage();
    public:
        ~AbstractHttpMessage();
        bool containsHeader(std::string name);
        void getHeaders(std::string name, vector<Header *> &res);
        Header* getFirstHeader(std::string name);
        Header* getLastHeader(std::string name);
        void getAllHeaders(vector<Header*> &res);
        void addHeader(Header* header);
        void addHeader(std::string name, std::string value);
        void setHeader(Header* header);
        void setHeader(std::string name, std::string value);
        void setHeaders(vector<Header*> &headers);
        void removeHeader(Header* header);
        void removeHeaders(std::string name);
        HeaderIterator* headerIterator();
        HeaderIterator* headerIterator(std::string name);
        HttpParams* getParams() ;
        void setParams(HttpParams* params);
};
#endif
