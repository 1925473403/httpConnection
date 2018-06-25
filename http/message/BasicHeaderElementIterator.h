#include "HttpException.h"
#ifndef BASICHEADERELEMENTITERATOR_H
#define BASICHEADERELEMENTITERATOR_H
class BasicHeaderElementIterator : public HeaderElementIterator {
    private:
        HeaderIterator* headerIt;
        HeaderValueParser* parser;
        HeaderElement* currentElement;
        CharArrayBuffer buffer;
        ParserCursor* cursor;
    public:
        BasicHeaderElementIterator(HeaderIterator* ht, HeaderValueParser* p);
        BasicHeaderElementIterator(HeaderIterator* ht);
        BasicHeaderElementIterator(const BasicHeaderElementIterator&);
        BasicHeaderElementIterator& operator(const BasicHeaderElementIterator&);
        void bufferHeaderValue();
        void parseNextElement();
        bool hasNext();
        Header* nextHeader() throw (NoSuchElementException);
        Header* next() throw (NoSuchElementException);
        void remove() throw(UnsupportedOperationException);
};
#endif
