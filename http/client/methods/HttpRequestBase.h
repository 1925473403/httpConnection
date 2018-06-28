#include "HttpException.h"
#ifndef HTTPREQUESTBASE_H
#define HTTPREQUESTBASE_H
class HttpRequestBase : public AbstractHttpMessage, public HttpUriRequest, public AbortableHttpRequest {
    class Lock {
        pthread_mutex_t &lock;
        public:
            Lock(pthread_mutex_t &t) : lock(t) { 
                pthread_mutex_lock(&lock);
            }
            ~Lock() {
                pthread_mutex_unlock(&lock);
            }
    };
    private:
        pthread_mutex_t abortLock;
        bool aborted;
        URI uri;
        ClientConnectionRequest* connRequest;
        ConnectionReleaseTrigger* releaseTrigger;
    public:
        HttpRequestBase();
        std::string getMethod() = 0;
        ProtocolVersion* getProtocolVersion();
        URI getURI();
        RequestLine* getRequestLine();
        void setURI(URI uri);
        void setConnectionRequest(ClientConnectionRequest* connReq);
        void setReleaseTrigger(ConnectionReleaseTrigger* releaseTrig);
        void abort();
        bool isAborted();
};
#endif
