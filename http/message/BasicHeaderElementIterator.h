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
        BasicHeaderElementIterator& operator=(const BasicHeaderElementIterator&);
        ~BasicHeaderElementIterator();
        void bufferHeaderValue();
        void parseNextElement();
        bool hasNext();
        HeaderElement* nextElement() ;
        HeaderElement* next() throw (NoSuchElementException);
        void remove() throw(UnsupportedOperationException);
};
#endif
