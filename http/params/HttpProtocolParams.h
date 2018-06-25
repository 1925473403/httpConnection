#include "HttpException.h"
#ifndef HTTPPROTOCOLPARAMS_H
#define HTTPPROTOCOLPARAMS_H
class HttpProtocolParams : public CoreProtocolPNames {
        HttpProtocolParams() { }
    public:
        static std::string getHttpElementCharset(HttpParams *params);
        static void setHttpElementCharset(HttpParams *params,  std::string &charset) ;
        static std::string getContentCharset(HttpParams *params);
        static void setContentCharset(HttpParams *params,  std::string &charset) ;
        static ProtocolVersion* getVersion(HttpParams *params);
        static void setVersion(HttpParams *params,  ProtocolVersion*) ;
        static std::string getUserAgent(HttpParams *params);
        static void setUserAgent(HttpParams *params,  std::string &charset) ;
        static bool useExpectContinue(HttpParams *params);
        static void setUseExpectContinue(HttpParams *params,  bool) ;
};
#endif
