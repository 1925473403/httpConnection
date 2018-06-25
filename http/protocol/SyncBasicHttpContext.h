#include "HttpException.h"
#ifndef SYNCBASICHTTPCONTEXT_H
#define SYNCBASICHTTPCONTEXT_H
class SyncBasicHttpContext : public BasicHttpContext {
        static pthread_mutex_t mutex;
        class Lock {
            pthread_mutex_t &lck;
            public:
                Lock(pthread_mutex_t &m) : lck(m) {
                    pthread_mutex_lock(&lck);
                }
                ~Lock() { pthread_mutex_unlock(&lck); }
        };
    public:
        SyncBasicHttpContext(HttpContext *context);
        ValueBase *getAttribute(std::string id);
        void setAttribute(std::string id, ValueBase *obj);
        ValueBase *removeAttribute(std::string id);
};
#endif
