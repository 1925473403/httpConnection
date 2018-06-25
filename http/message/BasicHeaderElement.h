#include "HttpException.h"
#include "NameValuePair.h"
#ifndef BASICHEADERELEMENT_H
#define BASICHEADERELEMENT_H
class BasicHeaderElement : public HeaderElement {
    private:
    std::string name;
    std::string value;
    std::vector<NameValuePair *> parameters;
    BasicHeaderElement(const BasicHeaderElement &rhs);
    BasicHeaderElement& operator=(const BasicHeaderElement &);
    public:
    BasicHeaderElement(std::string name, std::string value, std::vector<NameValuePair *> &parameters);
    BasicHeaderElement(std::string name, std::string value);
    ~BasicHeaderElement();
    std::string getName() const { return name; }
    std::string getValue() const { return value; }
    void getParameters(vector<NameValuePair *> &res);
    int getParameterCount() const { return parameters.size(); }
    NameValuePair* getParameter(int index);
    NameValuePair* getParameterByName(std::string name);
    bool equals(HeaderElement *);
    int hashCode();
    std::string toString();
};
#endif
