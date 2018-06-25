#include "HttpException.h"
#include "HttpParams.h"
#include "HttpAbstractParamBean.h"
#include "CoreConnectionPNames.h"
#include "HttpConnectionParams.h"
#ifndef HTTPcONNECTIONPARAMBEAN_H
#include "HttpConnectionParamBean.h"
#endif
HttpConnectionParamBean::HttpConnectionParamBean(HttpParams *p) : HttpAbstractParamBean (p) {
}

HttpConnectionParamBean::~HttpConnectionParamBean() {
}

void HttpConnectionParamBean::setSoTimeout (int soTimeout) {
    HttpConnectionParams::setSoTimeout(params, soTimeout);
}

void HttpConnectionParamBean::setTcpNoDelay (bool tcpNoDelay) {
    HttpConnectionParams::setTcpNoDelay(params, tcpNoDelay);
}

void HttpConnectionParamBean::setSocketBufferSize (int socketBufferSize) {
    HttpConnectionParams::setSocketBufferSize(params, socketBufferSize);
}

void HttpConnectionParamBean::setLinger (int linger) {
    HttpConnectionParams::setLinger(params, linger);
}

void HttpConnectionParamBean::setConnectionTimeout (int connectionTimeout) {
    HttpConnectionParams::setConnectionTimeout(params, connectionTimeout);
}

void HttpConnectionParamBean::setStaleCheckingEnabled (bool staleCheckingEnabled) {
    HttpConnectionParams::setStaleCheckingEnabled(params, staleCheckingEnabled);
}
