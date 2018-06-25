#include "HttpException.h"
#ifndef BASICHEADERITERATOR_H
#define BASICHEADERITERATOR_H
class BasicHeaderIterator : public HeaderIterator {
    protected:
        vector<Header *> &allHeaders;
        int currentIndex;
        std::string headerName;
    public:
        BasicHeaderIterator(vector<Header *> &headers, std::string name);
        BasicHeaderIterator(const BasicHeaderIterator&);
        BasicHeaderIterator& operator=(const BasicHeaderIterator&);
        int findNext(int from);
        bool filterHeader(int index);
        bool hasNext();
        Header* nextHeader() throw (NoSuchElementException);
        Header* next() throw (NoSuchElementException);
        void remove() throw(UnsupportedOperationException);
};
#endif
