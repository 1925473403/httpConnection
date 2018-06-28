#include "HttpException.h"
#ifndef HTTPOPTIONS_H
#define HTTPOPTIONS_H
class HttpOptions : public HttpRequestBase {
    public:
        static std::string METHOD_NAME;
        HttpOptions();
        HttpOptions(URI uri);
        HttpOptions(std::string uri);
        std::string getMethod();
        void getAllowedMethods(HttpResponse* method, std::unordered_set<std::string> &res);
};
#endif
