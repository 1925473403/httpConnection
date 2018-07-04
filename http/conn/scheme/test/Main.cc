#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "InetSocketAddress.h"
#include "CharArrayBuffer.h"
#include "HttpHost.h"
#include "HTTP.h"
//#include "SocketFactory.h"
//#include "Scheme.h"
//#include "SchemeRegistry.h"

int main(int argc, char **argv) {
    std::string host;
    std::cout << "Enter ip address: " ;
    cin >> host;
    InetAddress *addr = InetAddress::getByName(host);
    InetSocketAddress iaddr(addr, 5060);
    std::cout << *addr << std::endl;
    delete addr;
    return 0;
}
