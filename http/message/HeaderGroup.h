#include "HttpException.h"
#include "RefCount.h"
#ifndef HEADERGROUP_H
#define HEADERGROUP_H
class HeaderGroup : public RefCount {
    private:
    vector<Header *> headers;
    public:
        HeaderGroup();
        ~HeaderGroup();
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
