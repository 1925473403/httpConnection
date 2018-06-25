#include <pthread.h>
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
        SyncBasicHttpContext(HttpContext *context): BasicHttpContext(context) { }
        HttpContext *getAttribute(std::string &id) {
            HttpContext *obj = NULL;
            Lock l(mutex);
            obj = BasicHttpContext::getAttribute(id);
            return obj;
        }
        void setAttribute(std::string &id, HttpContext *obj) {
            Lock l(mutex);
            BasicHttpContext::setAttribute(id, obj);
        }
        HttpContext *removeAttribute(std::string &id) {
            HttpContext *obj = NULL;
            Lock l(mutex);
            obj = BasicHttpContext::removeAttribute(id);
            return obj;
        }
};
