#include "HttpException.h"
#include "Value.h"
#include "CoreConnectionPNames.h"
#include "HttpParams.h"
#ifndef HTTPCONNECTIONPARAMS_H
#include "HttpConnectionParams.h"
#endif
int HttpConnectionParams::getSoTimeout(HttpParams *params) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    return params->getIntParameter(CoreConnectionPNames::SO_TIMEOUT, 0);
}

void HttpConnectionParams::setSoTimeout(HttpParams *params, int timeout) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params->setIntParameter(CoreConnectionPNames::SO_TIMEOUT, timeout);
}

bool HttpConnectionParams::getTcpNoDelay(HttpParams *params) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    return params->getBooleanParameter(CoreConnectionPNames::TCP_NODELAY, true);
}

void HttpConnectionParams::setTcpNoDelay(HttpParams *params, bool value) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params->setBooleanParameter(CoreConnectionPNames::TCP_NODELAY, value);
}

int HttpConnectionParams::getSocketBufferSize(HttpParams *params) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    return params->getIntParameter(CoreConnectionPNames::SOCKET_BUFFER_SIZE, -1);
}

void HttpConnectionParams::setSocketBufferSize(HttpParams *params, int size) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params->setIntParameter(CoreConnectionPNames::SOCKET_BUFFER_SIZE, size);
}

int HttpConnectionParams::getLinger(HttpParams *params) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    return params->getIntParameter(CoreConnectionPNames::SO_LINGER, -1);
}

void HttpConnectionParams::setLinger(HttpParams *params, int value) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params->setIntParameter(CoreConnectionPNames::SO_LINGER, value);
}

int HttpConnectionParams::getConnectionTimeout(HttpParams *params) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    return params->getIntParameter(CoreConnectionPNames::CONNECTION_TIMEOUT, 0);
}

void HttpConnectionParams::setConnectionTimeout(HttpParams *params, int timeout) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params->setIntParameter(CoreConnectionPNames::CONNECTION_TIMEOUT, timeout);
}

bool isStaleCheckingEnabled(HttpParams *params) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    return params->getBooleanParameter(CoreConnectionPNames::STALE_CONNECTION_CHECK, true);
}

void HttpConnectionParams::setStaleCheckingEnabled(HttpParams *params, bool value) {
    if (params == NULL) throw IllegalArgumentException("HTTP parameters may not be null");
    params->setBooleanParameter(CoreConnectionPNames::STALE_CONNECTION_CHECK, value);
}
