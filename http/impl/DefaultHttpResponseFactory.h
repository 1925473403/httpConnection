#include "HttpException.h"
#ifndef DEFAULTHTTPRESPONSEFACTORY_H
#define DEFAULTHTTPRESPONSEFACTORY_H
class DefaultHttpResponseFactory : public HttpResponseFactory {
    protected:
        ReasonPhraseCatalog *reasonCatalog;
    public:
        DefaultHttpResponseFactory() ;
        ~DefaultHttpResponseFactory();
        DefaultHttpResponseFactory(ReasonPhraseCatalog *catalog);
        HttpResponse* newHttpResponse(StatusLine* statusline, HttpContext *context);
        HttpResponse* newHttpResponse(ProtocolVersion *ver, int status, HttpContext *context);
};
#endif
