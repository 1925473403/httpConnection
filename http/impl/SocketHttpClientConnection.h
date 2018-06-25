#include "HttpException.h"
#ifndef SOCKETHTTPCLIENTCONNECTION_H
#define SOCKETHTTPCLIENTCONNECTION_H
class SocketHttpClientConnection:public AbstractHttpClientConnection, HttpInetConnection {
    private:
        volatile bool open;
        Socket socket;
    protected:
        void assertNotOpen() { 
            if (open) throw IllegalStateException("Connection is already open");
        }
        void assertOpen() {
            if (!open) throw IllegalStateException("Connection is not open");
        }
        SessionInputBuffer* createSessionInputBuffer(Socket &, int, HttpParams*) throws IOException;
        SessionOutputBuffer* createSessionOutputBuffer(Socket &, int, HttpParams*) throws IOException;
        void bind(Socket &,HttpParams*) throws IOException;
    public:
        SocketHttpClientConnection();
        ~SocketHttpClientConnection();
        bool isOpen() const { return open; }
        Socket& getSocket() { return socket; }
        TCPAddr getLocalAddress();
        int getLocalPort() const;
        TCPAddr getRemoteAddress();
        int getRemotePort() const;
        void setSocketTimeout(int timeout);
        int getSocketTimeout() const;
        void shutdown() throws IOException;
        void close() throws IOException;
};
#endif
