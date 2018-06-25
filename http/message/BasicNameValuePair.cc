#include "HttpException.h"
#include "CharArrayBuffer.h"
#include "NameValuePair.h"
#ifndef BASICNAMEVALUEPAIR_H
#include "BasicNameValuePair.h"
#endif
BasicNameValuePair::BasicNameValuePair(std::string n, std::string v) : name(n), value(v) { }
std::string BasicNameValuePair::toString() {
    int len = name.length();
    if (value.length() > 0) len += value.length() + 1;
    CharArrayBuffer buffer(len);
    buffer.append(name);
    if (value.length() > 0) {
        buffer.append("=");
        buffer.append(value);
    }
    return buffer.toString();
}
bool BasicNameValuePair::equals (NameValuePair *rhs) const {
    if (this == rhs) return true;
    BasicNameValuePair *that = dynamic_cast<BasicNameValuePair *>(rhs);
    if (that != NULL) {
        return ((name == that->getName()) && (value == that->getValue()));
    }
    return false;
}
int BasicNameValuePair::hashCode() {
    long hash = std::hash<std::string>{ } (name);
    hash ^= std::hash<std::string>{ } (value);
    return hash;
}
