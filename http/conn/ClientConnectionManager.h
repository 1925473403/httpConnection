#include "HttpException.h"
#ifndef CLIENTCONNECTIONMANAGER_H
#define CLIENTCONNECTIONMANAGER_H
class ClientConnectionManager {
    public:
        virtual ~ClientConnectionManager() { }
        virtual SchemeRegistry* getSchemeRegistry() = 0;
        virtual ClientConnectionRequest* requestConnection(HttpRoute* route, ValueBase* state) = 0;
        virtual void releaseConnection(ManagedClientConnection *conn, long validDuration, TimeUnit *timeUnit) = 0;
        virtual void closeIdleConnections(long idletime, TimeUnit *tunit) = 0;
        virtual void closeExpiredConnections() = 0;
        virtual void shutdown() = 0;
}
#endif
