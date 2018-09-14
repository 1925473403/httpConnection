#include "HttpException.h"
#include "RefCount.h"
#ifndef SOCKET_H
#define SOCKET_H
class SocketImpl;
class InputStream;
class OutputStream;
class SocketAddress;
class Socket:public RefCount {
    struct Lock {
        pthread_mutex_t &mutex;
        Lock(pthread_mutex_t& m):mutex(m) {
            pthread_mutex_lock(&mutex);
        }
        ~Lock() {
            pthread_mutex_unlock(&mutex);
        }
    };
    private:
        bool created;
        bool bound;
        bool connected;
        bool closed;
        pthread_mutex_t closeLock;
        bool shutIn;
        bool shutOut;
        bool oldImpl;
    public:
        SocketImpl *impl;
        Socket();
        ~Socket();
        Socket(SocketImpl* impl) ;
        Socket(std::string &host, int port);
        Socket(const char *host, int port);
        Socket(InetAddress *addr, int port);
        Socket(std::string &host, int port, InetAddress *localAddr, int localPort); 
        Socket(const char *host, int port, InetAddress *localAddr, int localPort) ;
        Socket(std::string &host, int port, bool stream) ;
        Socket(const char *host, int port, bool stream) ;
        Socket(InetAddress *addr, int port, bool stream) ;
        void setImpl();
        SocketImpl* getImpl();
        void createImpl();
        bool postAccept();
        InetAddress* getInetAddress();
        InetAddress* getLocalAddress();
        int getPort() ;
        int getLocalPort();
        void setConnected();
        void setBound();
        void setCreated();
        SocketAddress* getRemoteSocketAddress();
        SocketAddress* getLocalSocketAddress();
        InputStream* getInputStream() throw (IOException);
        OutputStream* getOutputStream() throw (IOException);
        void setTcpNoDelay(bool on) throw (SocketException);
        bool getTcpNoDelay() throw(SocketException);
        void setSoLinger(bool on, int linger) throw (SocketException);
        int getSoLinger() throw (SocketException);
        void setSoTimeout(int timeout) throw (SocketException);
        int getSoTimeout() throw (SocketException);
        void setSendBufferSize(int size) throw (SocketException);
        int getSendBufferSize() throw (SocketException);
        void setReceiveBufferSize(int size)throw (SocketException);
        int getReceiveBufferSize() throw (SocketException);
        void setKeepAlive(bool on) throw (SocketException);
        bool getKeepAlive() throw (SocketException);
        void setReuseAddress(bool on) throw (SocketException);
        bool getReuseAddress() throw (SocketException);
        void close() throw (IOException);
        void shutdownInput() throw (IOException);
        void shutdownOutput() throw (IOException);
        std::string toString();
        bool isConnected();
        bool isBound();
        bool isClosed();
        bool isInputShutdown();
        bool isOutputShutdown();
};
#endif
