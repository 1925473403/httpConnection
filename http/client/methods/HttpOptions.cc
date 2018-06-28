#include "HttpException.h"
#ifndef HTTPOPTIONS_H
#include "HttpOptions.h"
#endif
std::string HttpOptions::METHOD_NAME("OPTIONS");
HttpOptions::HttpOptions() {
}
HttpOptions::HttpOptions(URI uri) {
    setURI(uri);
}
HttpOptions::HttpOptions(std::string uri) {
    setURI(URI::create(uri));
}
std::string HttpOptions::getMethod() { return METHOD_NAME; }
void HttpOptions::getAllowedMethods(HttpResponse* response, std::unordered_set<std::string> &res) {
    if (response == NULL) throw  IllegalArgumentException("HTTP response may not be null");
    HeaderIterator *it = response->headerIterator("Allow");
    while (it->hasNext()) {
        Header *header = it->nextHeader();
        vector<HeaderElement *> elements;
        header->getElements(elements);
        for (HeaderElement *element : elements) {
            res.insert(element->getName());
        }
    }
}
