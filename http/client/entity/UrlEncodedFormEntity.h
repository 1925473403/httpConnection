#include "HttpException.h"
#ifndef URLENCODEDFORMENTITY_H
#define URLENCODEDFORMENTITY_H
class UrlEncodedFormEntity : public StringEntity {
    public:
        UrlEncodedFormEntity(vector<NameValuePair *> &parameters, std::string encoding) ;
        UrlEncodedFormEntity(vector<NameValuePair *> &parameters) ;
};
#endif
