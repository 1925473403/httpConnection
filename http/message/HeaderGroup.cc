#include "Header.h"
#include "HttpHost.h"
#include "CharArrayBuffer.h"
#include "BasicHeader.h"
#include "HeaderIterator.h"
#include "BasicListHeaderIterator.h"
#ifndef HEADERGROUP_H
#include "HeaderGroup.h"
#endif
HeaderGroup::HeaderGroup() {
}

void HeaderGroup::clear() {
    headers.clear();
}

void HeaderGroup::addHeader(Header *header) {
    if (header == NULL) return;
    headers.push_back(header);
}

void HeaderGroup::removeHeader(Header *header) {
    if (header == NULL) return;
    int i = 0;
    for (i = 0; i < headers.size(); i++) if (headers[i] == header) break;
    if (i < headers.size()) headers.erase(headers.begin() + i);
}

void HeaderGroup::updateHeader(Header *header) {
    if (header == NULL) return;
    for (int i = 0; i < headers.size(); i++) {
        if (headers[i]->getName() == header->getName()) {
            Header *h = headers[i];
            headers[i] = header;
            delete h;
            return;
        }
    }
    headers.push_back(header);
}

void HeaderGroup::setHeaders(vector<Header *>& rhs) {
    if (rhs.size() == 0) return;
    clear();
    for (int i = 0; i < rhs.size(); i++) headers.push_back(rhs[i]);
}

Header* HeaderGroup::getCondensedHeader(std::string name) {
    vector<Header *> res;
    getHeaders(name, res);
    if (res.size() == 0) return NULL;
    else if (headers.size() == 1) return headers[0];
    else {
        CharArrayBuffer valueBuffer(128);
        valueBuffer.append(headers[0]->getValue().c_str());
        for (int i = 1; i < res.size(); i++) {
            valueBuffer.append(", ");
            valueBuffer.append(headers[i]->getValue().c_str());
        }
        return new BasicHeader(HttpHost::toLowerCase(name), valueBuffer.toString());
    }
}

void HeaderGroup::getHeaders(std::string name, std::vector<Header *> &res) {
    for (int i = 0; i < headers.size(); i++) {
        if (headers[i]->getName() == name) res.push_back(headers[i]);
    }
}

Header* HeaderGroup::getFirstHeader(std::string name) {
    for (int i = 0; i < headers.size(); i++) {
        if (headers[i]->getName() == name) return headers[i];
    }
    return NULL;
}

Header* HeaderGroup::getLastHeader(std::string name) {
    for (int i = headers.size() - 1; i >= 0; i--)
        if (headers[i]->getName() == name) return headers[i];
    return NULL;
}

void HeaderGroup::getAllHeaders(vector<Header *> &res) {
    for(int i = 0; i < headers.size(); i++) res.push_back(headers[i]);
}

bool HeaderGroup::containsHeader(std::string name) {
    for (int i = 0; i < headers.size(); i++)
        if (headers[i]->getName() == name) return true;
    return false;
}

HeaderIterator* HeaderGroup::iterator() {
    return new BasicListHeaderIterator(headers, "");
}

HeaderIterator* HeaderGroup::iterator(std::string name) {
    return new BasicListHeaderIterator(headers, name);
}
