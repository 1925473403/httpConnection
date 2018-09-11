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
    for (Header* h : headers) {
        h->unref();
    }
    headers.clear();
}

HeaderGroup::~HeaderGroup() {
    clear();
}

void HeaderGroup::addHeader(Header *header) {
    if (header == NULL) return;
    header->ref();
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
    header->ref();
    for (int i = 0; i < headers.size(); i++) {
        if (headers[i]->getName() == header->getName()) {
            Header *h = headers[i];
            headers[i] = header;
            h->unref();
            return;
        }
    }
    headers.push_back(header);
}

void HeaderGroup::setHeaders(vector<Header *>& rhs) {
    if (rhs.size() == 0) return;
    clear();
    for (Header* h: rhs) {
        if (h) {
            h->ref();
            headers.push_back(h);
        }
    }
}

Header* HeaderGroup::getCondensedHeader(std::string name) {
    vector<Header *> res;
    getHeaders(name, res);
    if (res.size() == 0) return NULL;
    else if (headers.size() == 1) {
        return res[0];
    } else {
        CharArrayBuffer valueBuffer(128);
        valueBuffer.append(headers[0]->getValue().c_str());
        for (int i = 1; i < res.size(); i++) {
            valueBuffer.append(", ");
            valueBuffer.append(headers[i]->getValue().c_str());
        }
        for (Header *h : res) {
            h->unref();
        }
        res.clear();
        return new BasicHeader(HttpHost::toLowerCase(name), valueBuffer.toString());
    }
}

void HeaderGroup::getHeaders(std::string name, std::vector<Header *> &res) {
    for (Header *h : headers) {
        if (h != NULL) {
            if (h->getName() == name) {
                h->ref();
                res.push_back(h);
            }
        }
    }
}

Header* HeaderGroup::getFirstHeader(std::string name) {
    for (int i = 0; i < headers.size(); i++) {
        if (headers[i]->getName() == name) {
            headers[i]->ref();
            return headers[i];
        }
    }
    return NULL;
}

Header* HeaderGroup::getLastHeader(std::string name) {
    for (int i = headers.size() - 1; i >= 0; i--)
        if (headers[i]->getName() == name) {
            headers[i]->ref();
            return headers[i];
        }
    return NULL;
}

void HeaderGroup::getAllHeaders(vector<Header *> &res) {
    for (Header *h: headers) {
        if (h != NULL) {
            h->ref();
            res.push_back(h);
        }
    }
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
