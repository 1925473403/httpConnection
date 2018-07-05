#include "HttpException.h"
#ifndef SOCKETHTTPCLIENTCONNECTION_H
#define SOCKETHTTPCLIENTCONNECTION_H
class SocketHttpClientConnection:public AbstractHttpClientConnection, public HttpInetConnection {
    private:
        volatile bool open;
        Socket *socket;
    protected:
        void assertNotOpen() { 
            if (open) throw IllegalStateException("Connection is already open");
        }
        void assertOpen() {
            if (!open) throw IllegalStateException("Connection is not open");
        }
        SessionInputBuffer* createSessionInputBuffer(Socket *, int, HttpParams*) throw (IOException);
        SessionOutputBuffer* createSessionOutputBuffer(Socket *, int, HttpParams*) throw (IOException);
        void bind(Socket &,HttpParams*) throw (IOException);
    public:
        SocketHttpClientConnection();
        ~SocketHttpClientConnection();
        bool isOpen() const { return open; }
        Socket* getSocket() { return socket; }
        InetAddress* getLocalAddress();
        int getLocalPort() const;
        InetAddress* getRemoteAddress();
        int getRemotePort() const;
        void setSocketTimeout(int timeout);
        int getSocketTimeout() const;
        void shutdown() throw (IOException);
        void close() throw (IOException);
};
#endif
