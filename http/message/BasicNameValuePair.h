#include "HttpException.h"
#include "CharArrayBuffer.h"
#ifndef BASICNAMEVALUEPAIR_H
#define BASICNAMEVALUEPAIR_H
class BasicNameValuePair : public NameValuePair {
    private:
    std::string name;
    std::string value;
    BasicNameValuePair(const BasicNameValuePair& rhs){ }
    BasicNameValuePair& operator= (const BasicNameValuePair& rhs) { }
    public:
    ~BasicNameValuePair() { }
    BasicNameValuePair(std::string, std::string);
    std::string getName() const { return name; }
    std::string getValue() const { return value; }
    std::string toString();
    bool equals (NameValuePair *) const;
    int hashCode() ;
};
#endif
