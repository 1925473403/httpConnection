#include "HttpException.h"
#include "HeaderElement.h"
#ifndef BASICHEADERELEMENT_H
#include "BasicHeaderElement.h"
#endif
BasicHeaderElement::BasicHeaderElement(std::string n, std::string v, std::vector<NameValuePair *> &p) : name(n), value(v){
    if (name.length() == 0) throw IllegalArgumentException("Name may not be null");
    for (NameValuePair *nv: p) {
        if (nv != NULL) {
            nv->ref();
            parameters.push_back(nv);
        }
    }
}

BasicHeaderElement::BasicHeaderElement(std::string n, std::string v):name(n), value(v) {
}

BasicHeaderElement::~BasicHeaderElement() {
    for (NameValuePair *nvp : parameters) {
        if (nvp != NULL) nvp->unref();
    }
    parameters.clear();
}

void BasicHeaderElement::getParameters(vector<NameValuePair *> &res) {
    for (int i = 0; i < parameters.size(); i++) {
        if (parameters[i] != NULL) {
            parameters[i]->ref();
            res.push_back(parameters[i]);
        }
    }
}

NameValuePair* BasicHeaderElement::getParameter(int index) {
    NameValuePair *nv = NULL;
    if (index < parameters.size() && index > 0) {
        nv = parameters[index];
        nv->ref();
    }
    return nv;
}

NameValuePair* BasicHeaderElement::getParameterByName(std::string name) {
    if (name.length() == 0) throw IllegalArgumentException("Name may not be null");
    NameValuePair *found = 0;
    for (int i = 0; i < parameters.size(); i++) {
        if (parameters[i]->getName() == name) {
            found = parameters[i];
            found->ref();
            break;
        }
    }
    return found;
}

bool BasicHeaderElement::equals(HeaderElement *rhs) {
    if (this == rhs) return true;
    BasicHeaderElement *_rhs = dynamic_cast<BasicHeaderElement *>(rhs);
    if (_rhs != NULL) {
        return ((name == _rhs->getName()) && (value == _rhs->getValue()));
    }
    return false;
}

int BasicHeaderElement::hashCode() {
    return 0;
}

std::string BasicHeaderElement::toString() {
    return "";
}
