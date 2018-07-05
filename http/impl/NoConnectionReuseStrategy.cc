#include "HttpException.h"
#ifndef NOCONNECTIONREUSESTRATEGY_H
#include "NoConnectionReuseStrategy.h"
#endif
bool NoConnectionReuseStrategy::keepAlive(HttpResponse *response, HttpContext *context) {
    if (response == NULL) throw IllegalArgumentException("HTTP response may not be null");
    if (context == NULL) throw IllegalArgumentException("HTTP context may not be null");
    return false;
}
