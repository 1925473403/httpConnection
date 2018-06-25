#include "HttpException.h"
#ifndef HTTPCONNECTIONPARAMBEAN_H
#define HTTPCONNECTIONPARAMBEAN_H
class HttpConnectionParamBean : public HttpAbstractParamBean {
    public:
    HttpConnectionParamBean(HttpParams *p);
    ~HttpConnectionParamBean();
    void setSoTimeout (int soTimeout);
    void setTcpNoDelay (bool tcpNoDelay);
    void setSocketBufferSize (int socketBufferSize);
    void setLinger (int linger);
    void setConnectionTimeout (int connectionTimeout);
    void setStaleCheckingEnabled (bool staleCheckingEnabled);
};
#endif
