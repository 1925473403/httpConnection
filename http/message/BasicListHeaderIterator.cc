#include "HttpException.h"
#include "CharArrayBuffer.h"
#include "HeaderIterator.h"
#include "Header.h"
#include <iterator>
#include <algorithm>
#ifndef BASICLISTHEADERITERATOR_H
#include "BasicListHeaderIterator.h"
#endif
BasicListHeaderIterator::BasicListHeaderIterator(vector<Header *> &headers, std::string name):allHeaders(headers), headerName(name) {
    if (headers.size() == 0) throw IllegalArgumentException("Header list must not be null.");
    currentIndex = findNext(-1);
    lastIndex = -1;
}

BasicListHeaderIterator::BasicListHeaderIterator(const BasicListHeaderIterator& rhs) : allHeaders(rhs.allHeaders) {
    currentIndex = rhs.currentIndex;
    lastIndex = rhs.lastIndex;
    headerName = rhs.headerName;
    //std::copy(rhs.allHeaders.begin(), rhs.allHeaders.end(), std::back_inserter(allHeaders));
}

BasicListHeaderIterator& BasicListHeaderIterator::operator=(const BasicListHeaderIterator& rhs) {
    if (this != &rhs) {
        currentIndex = rhs.currentIndex;
        lastIndex = rhs.lastIndex;
        headerName = rhs.headerName;
        std::copy(rhs.allHeaders.begin(), rhs.allHeaders.end(), std::back_inserter(allHeaders));
    }
    return *this;
}

int BasicListHeaderIterator::findNext(int from) {
    if (from < -1) return -1;
    int to = allHeaders.size() - 1;
    bool found = false;
    while (!found && (from < to)) {
        from++;
        found = filterHeader(from);
    }
    return ((found)? from : -1);
}

bool BasicListHeaderIterator::filterHeader(int index) {
    if (headerName.length() == 0) return true;
    std::string name = allHeaders[index]->getName();
    return (name == headerName);
}

bool BasicListHeaderIterator::hasNext() {
    return currentIndex >= 0;
}

Header* BasicListHeaderIterator::nextHeader() throw (NoSuchElementException) {
    int current = currentIndex;
    if (current < 0) throw NoSuchElementException("Iteration already finished.");
    lastIndex = current;
    currentIndex = findNext(current);
    return allHeaders[current];
}

Header* BasicListHeaderIterator::next() throw (NoSuchElementException) {
    return nextHeader();
}

void BasicListHeaderIterator::remove() throw(UnsupportedOperationException) {
    if (lastIndex < 0) throw IllegalStateException("No header to remove.");
    Header * h = allHeaders[lastIndex];
    allHeaders.erase(allHeaders.begin() + lastIndex);
    delete h;
    lastIndex = -1;
    currentIndex--;
}
