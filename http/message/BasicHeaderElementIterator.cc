#include "HttpException.h"
#include "CharArrayBuffer.h"
#include "HeaderElement.h"
#include "ParserCursor.h"
#include "HTTP.h"
#include "HeaderValueParser.h"
#include "Header.h"
#include "FormattedHeader.h"
#include "HeaderIterator.h"
#include "HeaderElementIterator.h"
#include "BasicHeaderValueParser.h"
#ifndef BASICHEADERELEMENTITERATOR_H
#include "BasicHeaderElementIterator.h"
#endif
BasicHeaderElementIterator::BasicHeaderElementIterator(HeaderIterator* ht, HeaderValueParser* p) : headerIt(ht), parser(p), buffer(0) {
    if (headerIt == NULL) throw IllegalArgumentException("Header iterator may not be NULL");
    if (parser == NULL) throw IllegalArgumentException("Parser may not be NULL");
}

BasicHeaderElementIterator::BasicHeaderElementIterator(HeaderIterator* ht) : BasicHeaderElementIterator(ht, &BasicHeaderValueParser::DEFAULT) {
}

BasicHeaderElementIterator::BasicHeaderElementIterator(const BasicHeaderElementIterator& rhs): buffer(rhs.buffer) {
    cursor = rhs.cursor;
    parser = rhs.parser;
    headerIt = rhs.headerIt;
}

BasicHeaderElementIterator& BasicHeaderElementIterator::operator=(const BasicHeaderElementIterator& rhs) {
    if (this != &rhs) {
        buffer = rhs.buffer;
        cursor = rhs.cursor;
        parser = rhs.parser;
        headerIt = rhs.headerIt;
    } 
    return *this;
}

BasicHeaderElementIterator::~BasicHeaderElementIterator() { }

void BasicHeaderElementIterator::bufferHeaderValue() {
    cursor = NULL;
    while (headerIt->hasNext()) {
        Header *h = headerIt->nextHeader();
        FormattedHeader *fh = dynamic_cast<FormattedHeader*>(h);
        if (fh != NULL) {
            buffer = fh->getBuffer();
            cursor = new ParserCursor(0, buffer.length());
            cursor->updatePos(fh->getValuePos());
            break;
        } else {
            std::string value = h->getValue();
            if (value.length() > 0) {
                buffer = CharArrayBuffer(value.length());
                buffer.append(value.c_str());
                cursor = new ParserCursor(0, buffer.length());
                break;
            }
        }
    }
}

void BasicHeaderElementIterator::parseNextElement() {
    while (headerIt->hasNext() || cursor != NULL) {
        if (cursor == NULL || cursor->atEnd()) {
            bufferHeaderValue();
        }
        if (cursor != NULL) {
            while (!cursor->atEnd()) {
                HeaderElement *e = parser->parseHeaderElement(buffer, cursor);
                if (e->getName().length() != 0 && e->getValue().length() != 0) {
                    currentElement = e; return;
                }
            }
            if (cursor->atEnd()) {
                delete cursor;
                cursor = NULL;
                //buffer = NULL;
            }
        }
    }
}

bool BasicHeaderElementIterator::hasNext() {
    if (currentElement == NULL) parseNextElement();
    return currentElement != NULL;
}

HeaderElement* BasicHeaderElementIterator::nextElement() {
    if (currentElement == NULL) parseNextElement();
    if (currentElement == NULL) throw NoSuchElementException("No more header elements available");
    HeaderElement *element = currentElement;
    currentElement = NULL;
    return element;
}

HeaderElement* BasicHeaderElementIterator::next() throw (NoSuchElementException) {
    return nextElement();
}

void BasicHeaderElementIterator::remove() throw(UnsupportedOperationException) {
    throw UnsupportedOperationException("Remove not supported");
}
