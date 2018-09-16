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

void reverse(char *buf, int n) {
    return;
    int i = 0, j = 0;
    if (n > 0 && (strstr(buf, " ") != NULL)) {
        while (i < n) {
            for (; i < n; i++)
                if (buf[i] == ' ') break;
            for (int k = i-1; j < n && j < k; j++, k--) std::swap(buf[k], buf[j]);
            j = ++i;
        }
    }
    i = 0, j = n - 1;
    while (i < j) {
        std::swap(buf[i++], buf[j--]);
    }
}

int main() {
    int port = 0;
    try {
        std::string hostIp;
        cin >> hostIp;
        if (std::regex_match(hostIp, std::regex("([0-9]+).([0-9]+).([0-9]+).([0-9]+)")))
            std::cout << hostIp << " is an ip address" << std::endl;
        else std::cout << hostIp << " is not ip address" << std::endl;
        std::cout << "Enter server port: ";
        cin >> port ;
        ServerSocket s(htons(port));
        Socket *clientSocket = s.accept();
        if (clientSocket) {
            OutputStream *o = clientSocket->getOutputStream();
            InputStream *i = clientSocket->getInputStream();
            char buf[512] = { 0 };
            int n = 0;
            while ((n = i->read(buf, 512, 512)) > 0) {
                if (strlen(buf)) {
                    printf("{%d}[%.*s]", n, n, buf);
                    reverse((char *)buf, n);
                    o->write(buf, 512, n);
                    if (memcmp(buf, "quit", 4) == 0) break;
                }
            }
        }
        clientSocket->unref();
        std::cout << "client unreffed" << std::endl;
    } catch (const IOException &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
