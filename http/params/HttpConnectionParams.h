#include "HttpException.h"
#ifndef HTTPCONNECTIONPARAMS_H
#define HTTPCONNECTIONPARAMS_H
class HttpConnectionParams:public CoreConnectionPNames {
    public:
    HttpConnectionParams() { }
    ~HttpConnectionParams() { }
    static int getSoTimeout(HttpParams *params);
    static void setSoTimeout(HttpParams *params, int timeout);
    static bool getTcpNoDelay(HttpParams *params);
    static void setTcpNoDelay(HttpParams *params, bool value);
    static int getSocketBufferSize(HttpParams *params);
    static void setSocketBufferSize(HttpParams *params, int size);
    static int getLinger(HttpParams *params);
    static void setLinger(HttpParams *params, int value);
    static int getConnectionTimeout(HttpParams *params);
    static void setConnectionTimeout(HttpParams *params, int timeout);
    static bool isStaleCheckingEnabled(HttpParams *params);
    static void setStaleCheckingEnabled(HttpParams *params, bool value);
};
#endif
