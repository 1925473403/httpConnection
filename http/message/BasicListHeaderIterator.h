#include "HttpException.h"
#ifndef BASICLISTHEADERITERATOR_H
#define BASICLISTHEADERITERATOR_H
class BasicListHeaderIterator : public HeaderIterator {
    protected:
        vector<Header *> &allHeaders;
        int currentIndex;
        int lastIndex;
        std::string headerName;
    public:
        BasicListHeaderIterator(vector<Header *> &headers, std::string name);
        BasicListHeaderIterator(const BasicListHeaderIterator&);
        BasicListHeaderIterator& operator=(const BasicListHeaderIterator&);
        int findNext(int from);
        bool filterHeader(int index);
        bool hasNext();
        Header* nextHeader() throw (NoSuchElementException);
        Header* next() throw (NoSuchElementException);
        void remove() throw(UnsupportedOperationException);
};
#endif
