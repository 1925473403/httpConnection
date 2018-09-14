#include "HttpException.h"
#include "RefCount.h"
#ifndef SOCKET_H
#include "Socket.h"
#endif
#ifndef SOCKETIMPL_H
#define SOCKETIMPL_H
class InetAddress;
class InputStream;
class OutputStream;
class ServerSocket;
class SocketImpl : virtual public RefCount {
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
        virtual void connect(std::string &host, int p) throw (IOException) = 0;
        virtual void connect(const char *, int p) throw (IOException) = 0;
        virtual void bind(InetAddress *host, int p) throw (IOException) = 0;
        virtual void listen(int baclog) throw (IOException) = 0;
        virtual void accept(SocketImpl *s)throw (IOException)  = 0;
        virtual InputStream *getInputStream() throw (IOException) = 0;
        virtual OutputStream *getOutputStream() throw (IOException) = 0;
        virtual int available() throw (IOException) = 0;
        virtual void close() throw (IOException) = 0;
        virtual void sendUrgentData (int data) throw (IOException) = 0;
        void setSocket(Socket *s) { socket = s; }
        Socket* getSocket() { return socket; }
        virtual ~SocketImpl() { }
        virtual void shutdownInput() = 0;
        virtual void shutdownOutput() = 0;
        virtual int getFileDescriptor() = 0;
        virtual void setFileDescriptor(int) = 0;
        virtual int getPort() { return port; }
        virtual InetAddress *getInetAddress() { return address; }
        void setPort(int p) { port = p; }
        void setServerSocket(ServerSocket *s) { serverSocket = s; }
        ServerSocket* getServerSocket() { return serverSocket; }
        void setLocalPort(int p) { localport = p; }
        void setAddress(InetAddress *addr) { address = addr; }
        virtual int getLocalPort() { return localport; }
        virtual void setOption(int opt, int val) = 0;
        virtual int getOption(int opt) = 0;
        virtual void socketCreate(bool isServer) throw(IOException) ;
        virtual void socketConnect(InetAddress *address, int port, int timeout) throw (IOException) ;
        virtual void socketBind(InetAddress *address, int port) throw (IOException)  = 0;
        virtual void socketListen(int count) throw (IOException) =0;
        virtual void socketAccept(SocketImpl *s) throw (IOException)=0 ;
        virtual int socketAvailable() throw (IOException) =0;
        virtual void socketShutdown(int howto) throw (IOException) =0;
        virtual void socketSendUrgentData(int data) throw (IOException)=0 ;
        virtual void reset() throw (IOException);
        virtual std::string toString(); 
};
#endif
