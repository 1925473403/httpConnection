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
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
using namespace std;

int main() {
    int port = 0;
    try {
        cin >> port ;
        Socket s("www.google.com", htons(port));
        OutputStream *o = s.getOutputStream();
        InputStream *i = s.getInputStream();
        char buf[512] = { 0 };
        int n = 0;
        char *line = NULL;
        stringstream ss;
        ss << "GET / HTTP/1.1\r\n";
        ss << "Host: www.google.com\r\n";
        ss << "Accept: */*\r\n";
        ss << "\r\n";
        o->write((char *)ss.str().c_str(), ss.str().length(), ss.str().length());
        //cin.tie(NULL);
        while ((n = i->read(buf, 512, 512)) > 0) {
            printf("{%d}[%.*s]", n, n, buf);
            if (strstr(buf, "</html>") != NULL) break;
        }
    } catch (const IOException &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
