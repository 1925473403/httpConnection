#include "HttpException.h"
#ifndef HEADERGROUP_H
#define HEADERGROUP_H
class HeaderGroup {
    private:
    vector<Header *> headers;
    public:
        HeaderGroup();
        void clear();
        void addHeader(Header *);
        void removeHeader(Header *);
        void updateHeader(Header *);
        void setHeaders(vector<Header *>&);
        Header* getCondensedHeader(std::string name);
        void getHeaders(std::string name, vector<Header *> &res);
        Header* getFirstHeader(std::string name);
        Header* getLastHeader(std::string name);
        void getAllHeaders(vector<Header *> &res);
        bool containsHeader(std::string name);
        HeaderIterator* iterator();
        HeaderIterator* iterator(std::string name);
};
#endif
