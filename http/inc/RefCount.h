#include <iostream>
#include <assert.h>
#include <pthread.h>
using namespace std;
#ifndef REFCOUNT_H
#define REFCOUNT_H
class RefCount {
    struct Lock {
        pthread_mutex_t &mutex;
        Lock(pthread_mutex_t &m):mutex(m) {
            pthread_mutex_lock(&mutex);
        }
        ~Lock() { 
            pthread_mutex_unlock(&mutex); 
        }
    };
    size_t refcount;
    pthread_mutex_t m_mutex;
    protected:
    RefCount():refcount(1) { 
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&m_mutex, &attr);
    }
    virtual ~RefCount() { 
        assert(refcount == 0 || refcount == 1);
    }
    public:
    void ref() {
        {
            Lock l (m_mutex);
            assert(refcount > 0 && refcount < 1000000);
            refcount++;
        }
    }
    void unref() {
        {
            Lock l (m_mutex);
            assert(refcount > 0);
            refcount--;
            if (refcount == 0) delete this;
        }
    }
};
#endif
