#include "HttpException.h"
#ifndef ABSTRACTPLAINSOCKETIMPL_H
#define ABSTRACTPLAINSOCKETIMPL_H
class AbstractPlainSocketImpl : public SocketImpl {
    class Lock {
        pthread_mutex_t &m;
        public:
        Lock(pthread_mutex_t &t): m(t) {
            pthread_mutex_lock(&m);
        }
        ~Lock() { 
            pthread_mutex_unlock(&m);
        }
    };
    private:
        InputStream *socketInputStream;
        OutputStream *socketOutputStream;
        static int SHUT_RD;
        static int SHUT_WR;
        int CONNECTION_NOT_RESET;
        int CONNECTION_RESET_PENDING;
        int CONNECTION_RESET;
        int resetState;
        bool shut_rd;
        bool shut_wr;
        int trafficClass;
        int timeout;
    protected:
        pthread_mutex_t fdLock;
        pthread_mutex_t resetLock;
        bool closePending;
        int fdUseCount;
    public:
        void reset() throw (IOException);
        void create(bool stream);
        void connect(std::string &host, int port) throw (IOException);
        void connect(const char* host, int port) throw (IOException);
        void connect(InetAddress* addr, int p) throw (IOException) ;
        void connect(SocketAddress *, int) throw (IOException);
        void connectToAddress(InetAddress* addr, int p, int t) throw (IOException);
        void bind(InetAddress *host, int port) throw (IOException);
        void listen(int baclog) throw (IOException);
        void accept(SocketImpl *s) throw (IOException);
        InputStream *getInputStream() throw (IOException);
        OutputStream *getOutputStream() throw (IOException);
        void doConnect(InetAddress* addr, int port, int timeout) throw (IOException) ;
        int available() throw (IOException);
        void close() throw (IOException);
        void socketClose();
        AbstractPlainSocketImpl();
        void shutdownInput();
        void shutdownOutput();
        int getFileDescriptor() const { return fd; }
        void setOption(int opt, int val);
        int getOption(int opt);
        void sendUrgentData (int data) throw (IOException);
        int acquireFD();
        void releaseFD();
        int getTimeout();
        void setInputStream(InputStream *in) { socketInputStream = in; }
        void setFileDescriptor(int f) { fd = f; }
        void setAddress(InetAddress *addr) { address = addr; }
        void setPort(int p) { port = p; }
        void setLocalPort(int l) { localport = l; }
        bool isConnectionReset();
        bool isConnectionResetPending();
        void setConnectionReset();
        void setConnectionResetPending();
        bool isClosedOrPending();
        virtual void socketCreate(bool isServer) throw(IOException) = 0;
        virtual void socketConnect(InetAddress *address, int port, int timeout) throw (IOException) = 0;
        virtual void socketBind(InetAddress *address, int port) throw (IOException) = 0;
        virtual void socketListen(int count) throw (IOException) = 0;
        virtual void socketAccept(SocketImpl *s) throw (IOException) = 0;
        virtual int socketAvailable() throw (IOException) = 0;
        virtual void socketShutdown(int howto) throw (IOException) = 0;
        virtual void socketSendUrgentData(int data) throw (IOException) = 0;
        //virtual void socketPreClose();
};
#endif
