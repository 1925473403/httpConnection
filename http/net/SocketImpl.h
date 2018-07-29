#include "HttpException.h"
#ifndef SOCKETIMPL_H
#define SOCKETIMPL_H
class Socket;
class InetAddress;
class InputStream;
class OutputStream;
class ServerSocket;
class SocketImpl {
    private:
    protected:
        Socket *socket;
        ServerSocket *serverSocket;
        int port;
        int localport;
        int fd;
        InetAddress *address;
    public:
        virtual void create(bool stream) = 0;
        virtual void connect(std::string host, int port) = 0;
        virtual void bind(InetAddress *host, int port) = 0;
        virtual void listen(int baclog) = 0;
        virtual void accept(SocketImpl *s) = 0;
        virtual InputStream *getInputStream() = 0;
        virtual OutputStream *getOutputStream() = 0;
        virtual int available() = 0;
        virtual void close() = 0;
        virtual void sendUrgentData (int data) = 0;
        void setSocket(Socket *s) { socket = s; }
        Socket* getSocket() { return socket; }
        virtual ~SocketImpl() { }
        virtual void shutdownInput() = 0;
        virtual void shutdownOutput() = 0;
        virtual int getFileDescriptor() = 0;
        virtual int getPort() = 0;
        virtual InetAddress *getInetAddress() = 0;
        virtual int getLocalPort() = 0;
        virtual void setOption(int opt, int val) = 0;
        virtual int getOption(int opt) = 0;
        void socketCreate(bool isServer) throw(IOException) ;
        void socketConnect(InetAddress *address, int port, int timeout) throw (IOException) ;
        void socketBind(InetAddress *address, int port) throw (IOException) ;
        void socketListen(int count) throw (IOException) ;
        void socketAccept(SocketImpl *s) throw (IOException) ;
        int socketAvailable() throw (IOException) ;
        void socketShutdown(int howto) throw (IOException) ;
        void socketSendUrgentData(int data) throw (IOException) ;
};
#endif
