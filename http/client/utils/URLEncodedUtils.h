#include "HttpException.h"
#ifndef URLENCODEDUTILS_H
#define URLENCODEDUTILS_H
class URLEncodedUtils : public RefCount {
    private:
    std::string PARAMETER_SEPARATOR;
    std::string NAME_VALUE_SEPARATOR;
    public:
    std::string CONTENT_TYPE;
    static void parse(URI &uri, std::string &encoding, vector<NameValuePair *> &res);
    static void parse(HttpEntity *entity, vector<NameValuePair *> &res);
    static bool isEncoded(HttpEntity *entity);
    static void parse(Scanner *scanner, std::string &encoding, vector<NameValuePair *> &res);
    static std::string format(std::vector<NameValuePair *>&parameters, std::string &encoding);
    static std::string decode(std::string &content, std::string &encoding);
    static std::string encode(std::string &content, std::string &encoding);
};
#endif
