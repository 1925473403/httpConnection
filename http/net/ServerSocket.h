#include "RefCount.h"
#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
class ServerSocket : public RefCount {
    private:
        bool created;
        bool bound;
        bool closed;
        pthread_mutex_t closeLock;
        struct Lock {
            pthread_mutex_t &l;
            Lock(pthread_mutex_t &lo):l(lo) {
                pthread_mutex_lock(&l);
            }
            ~Lock() {
                pthread_mutex_unlock(&l);
            }
        };
        SocketImpl *impl;
        bool oldImpl;
    public:
        ServerSocket(SocketImpl *);
        ServerSocket(int p);
        ServerSocket(int port, int backlog);
        ServerSocket(int p, int backlog, InetAddress *bindAddr);
        SocketImpl* getImpl() throw (SocketException);
        void checkOldImpl();
        void setImpl();
        void createImpl() throw (SocketException);
        void bind(SocketAddress* endpoint) throw(IOException);
        void bind(SocketAddress* endpoint, int backlog) throw(IOException);
        InetAddress *getInetAddress();
        int getLocalPort();
        SocketAddress *getLocalSocketAddress();
        Socket *accept() throw(IOException);
        void implAccept(Socket *s) throw (IOException) ;
        void close() throw (IOException);
        bool isBound();
        bool isClosed();
        void setSoTimeout(int timeout) throw (SocketException);
        int getSoTimeout() throw (IOException) ;
        void setReuseAddress(bool on) throw (SocketException);
        bool getReuseAddress() throw (SocketException) ;
        std::string toString();
        void setBound();
        void setCreated();
        void setSocketFactory(SocketImplFactory *fac) throw(IOException);
        void setReceiveBufferSize (int size) throw(SocketException);
        int getReceiveBufferSize() throw(SocketException);
        static SocketImplFactory *factory;
};
#endif
