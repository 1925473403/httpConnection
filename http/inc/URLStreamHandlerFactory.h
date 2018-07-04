#include "HttpException.h"
#ifndef URLSTREAMHANDLERFACTORY_H
#define URLSTREAMHANDLERFACTORY_H
class URLStreamHandler;
class URLStreamHandlerFactory {
    public:
        virtual ~URLStreamHandlerFactory() { }
        virtual URLStreamHandler* createURLStreamHandler(std::string str) = 0;
};
#endif
