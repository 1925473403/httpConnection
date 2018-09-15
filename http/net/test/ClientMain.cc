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
#include <regex>
using namespace std;

int main() {
    int port = 0;
    try {
        cin >> port ;
        Socket s("localhost", port);
        OutputStream *o = s.getOutputStream();
        InputStream *i = s.getInputStream();
        char buf[512] = { 0 };
        size_t len;
        int n = 0;
        char *line = NULL;
        o->write("hi...", 512, 5);
        while ((n = i->read(buf, 512, 512)) > 0) {
            printf("{%d}[%.*s]", n, n, buf);
            if (memcmp(buf, "quit", 4) == 0) break;
            getline(&line, &len, stdin);
            o->write(line, len, len);
            if (memcmp(buf, "quit", 4) == 0) break;
        }
        free(line);
    } catch (const IOException &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
