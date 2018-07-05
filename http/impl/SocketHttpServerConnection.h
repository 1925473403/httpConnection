#include "HttpException.h"
#ifndef SOCKETHTTPSERVERCONNECTION_H
#define SOCKETHTTPSERVERCONNECTION_H
class SocketHttpServerConnection : public AbstractHttpServerConnection, public HttpInetConnection {
    private:
        bool open;
        Socket *socket;
    public:
        SocketHttpServerConnection();
    protected:
        void assertNotOpen() {
            if (open) throw IllegalStateException("Connection is already open");
        }
        void assertOpen() {
            if (!open) throw IllegalStateException("Connection is not open");
        }
        SessionInputBuffer* createHttpDataReceiver(Socket *sock, int buffersize, HttpParams *params) throw (IOException);
        SessionOutputBuffer* createHttpDataTransmitter(Socket *sock, int buffersize, HttpParams *params) throw (IOException);
        void bind(Socket *sock, HttpParams *params) throw (IOException);
        Socket* getSocket() { return socket; }
    public:
        bool isOpen() { return open; }
        InetAddress* getLocalAddress();
        InetAddress* getRemoteAddress();
        int getRemotePort();
        int getLocalPort();
        void setSocketTimeout(int timeout);
        int getSocketTimeout();
        void shutdown() throw (IOException);
        void close() throw (IOException);
};
#endif
