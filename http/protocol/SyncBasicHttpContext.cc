#include "Value.h"
#include "HttpContext.h"
#include "BasicHttpContext.h"
#ifndef SYNCBASICHTTPCONTEXT_H
#include "SyncBasicHttpContext.h"
#endif
pthread_mutex_t SyncBasicHttpContext::mutex;
SyncBasicHttpContext::SyncBasicHttpContext(HttpContext *context): BasicHttpContext(context) { 
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&mutex, &attr);
}
ValueBase *SyncBasicHttpContext::getAttribute(std::string id) {
    ValueBase *obj = NULL;
    Lock l(mutex);
    obj = BasicHttpContext::getAttribute(id);
    return obj;
}
void SyncBasicHttpContext::setAttribute(std::string id, ValueBase *obj) {
    Lock l(mutex);
    BasicHttpContext::setAttribute(id, obj);
}
ValueBase *SyncBasicHttpContext::removeAttribute(std::string id) {
    ValueBase *obj = NULL;
    Lock l(mutex);
    obj = BasicHttpContext::removeAttribute(id);
    return obj;
}
