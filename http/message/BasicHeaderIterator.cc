#include "HttpException.h"
#include <iterator>
#include <algorithm>
#ifndef BASICHEADERITERATOR_H
#include "BasicHeaderIterator.h"
#endif
BasicHeaderIterator::BasicHeaderIterator(vector<Header *> &headers, std::string name):allHeaders(headers), headerName(name) {
    if (headers.size() == 0) throw IllegalArgumentException("Header list must not be null.");
    currentIndex = findNext(-1);
}

BasicHeaderIterator::BasicHeaderIterator(const BasicHeaderIterator& rhs) {
    currentIndex = rhs.currentIndex;
    headerName = rhs.headerName;
    std::copy(rhs.allHeaders.begin(), rhs.allHeaders.end(), std::back_inserter(allHeaders));
}

BasicHeaderIterator& BasicHeaderIterator::operator=(const BasicHeaderIterator& rhs) {
    if (this != &rhs) {
        currentIndex = rhs.currentIndex;
        headerName = rhs.headerName;
        std::copy(rhs.allHeaders.begin(), rhs.allHeaders.end(), std::back_inserter(allHeaders));
    }
    return *this;
}

int BasicHeaderIterator::findNext(int from) {
    if (from < -1) return -1;
    int to = allHeaders.size() - 1;
    bool found = false;
    while (!found && (from < to)) {
        from++;
        found = filterHeader(from);
    }
    return ((found)? from : -1);
}

bool BasicHeaderIterator::filterHeader(int index) {
    if (headerName.length() == 0) return true;
    std::string name = allHeaders[index]->getName();
    return (name == headerName);
}

bool BasicHeaderIterator::hasNext() {
    return currentIndex >= 0;
}

Header* BasicHeaderIterator::nextHeader() throw (NoSuchElementException) {
    int current = currentIndex;
    if (current < 0) throw NoSuchElementException("Iteration already finished.");
    currentIndex = findNext(current);
    return allHeaders[current];
}

Header* BasicHeaderIterator::next() throw (NoSuchElementException) {
    return nextHeader();
}

void BasicHeaderIterator::remove() throw(UnsupportedOperationException) {
    throw UnsupportedOperationException("Removing headers is not supported.");
}
