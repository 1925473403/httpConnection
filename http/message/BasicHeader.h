#include "HttpException.h"
#ifndef BASICHEADER_H
#define BASICHEADER_H
class BasicHeader : public Header {
    private:
        std::string name;
        std::string value;
    protected:
    public:
        ~BasicHeader() { }
        std::string getName() { return name; }
        std::string getValue() { return value; }
        std::string toString();
        void getElements(vector<HeaderElement *> &) throw (ParseException) ;
        BasicHeader(std::string &n, std::string &v);
        BasicHeader(std::string &n, std::string &&v);
};
#endif
