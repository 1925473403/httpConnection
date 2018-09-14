#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include "HttpException.h"
#include "NameResolver.h"
#include "InetSocketAddress.h"
#include "SocketImpl.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "AbstractPlainSocketImpl.h"
#include "SocketInputStream.h"
#include "SocketOutputStream.h"
#include "URI.h"
#include "URL.h"
#include "URLStreamHandler.h"
#include "SocketImplFactory.h"
#include "Socket.h"
#include "ServerSocket.h"

int main() {
    try {
        ServerSocket s(65500);
        Socket *clientSocket = s.accept();
        if (clientSocket) {
            OutputStream *o = clientSocket->getOutputStream();
            InputStream *i = clientSocket->getInputStream();
        }
    } catch (const IOException &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
