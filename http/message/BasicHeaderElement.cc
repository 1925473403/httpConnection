#include "HttpException.h"
#include "HeaderElement.h"
#ifndef BASICHEADERELEMENT_H
#include "BasicHeaderElement.h"
#endif
BasicHeaderElement::BasicHeaderElement(std::string n, std::string v, std::vector<NameValuePair *> &p) : name(n), value(v){
    if (name.length() == 0) throw IllegalArgumentException("Name may not be null");
    for (int i = 0; i < p.size(); i++) parameters.push_back(p[i]);
}

BasicHeaderElement::BasicHeaderElement(std::string n, std::string v):name(n), value(v) {
}

BasicHeaderElement::~BasicHeaderElement() {
    parameters.clear();
}

void BasicHeaderElement::getParameters(vector<NameValuePair *> &res) {
    for (int i = 0; i < parameters.size(); i++) res.push_back(parameters[i]);
}

NameValuePair* BasicHeaderElement::getParameter(int index) {
    if (index < parameters.size() && index > 0) return parameters[index];
    return 0;
}

NameValuePair* BasicHeaderElement::getParameterByName(std::string name) {
    if (name.length() == 0) throw IllegalArgumentException("Name may not be null");
    NameValuePair *found = 0;
    for (int i = 0; i < parameters.size(); i++) {
        if (parameters[i]->getName() == name) return parameters[i];
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
