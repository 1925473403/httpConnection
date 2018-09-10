#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sys/socket.h> /* socklen_t, etc */
#include <sys/poll.h>
#include <sys/ioctl.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <exception>
#include <sstream>
#include <assert.h>
#include <errno.h>
#include <iostream>
#include <vector>
using namespace std;
#include "transport.h"

void host::resolve(char* str, vector<long> &v) {
    if (str == NULL) return;
    struct hostent *h  = gethostbyname(str);
    if (h) {
        std::cout << "Name: " << h->h_name << std::endl;
        std::cout << "Aliases: " ;
        for (int i = 0; (i < (1<<8)) && h->h_aliases[i]; i++) {
            std::cout << h->h_aliases[i];
            if (h->h_aliases[i+1]) std::cout << ", ";
        }
        std::cout << "\nType: " << h->h_addrtype << std::endl;
        std::cout << "Length: " << h->h_length << std::endl;
        std::cout << "List Of Addresses: " ;
        for (int i = 0; (i < h->h_length && h->h_addr_list[i]); i++) {
            stringstream ss;
            char *s = h->h_addr_list[i];
            ss << ((int)(s[0]&0xff)) << "." << ((int)(s[1]&0xff)) << "." << ((int)(s[2]&0xff)) << "." << ((int)(s[3]&0xff));
            std::cout << ss.str() ;
            v.push_back(*(long *)h->h_addr_list[i]);
        }
        std::cout << std::endl;
    }
    return;
}

void host::resolve(char* str, vector<string> &v) {
    if (str == NULL) return;
    struct hostent *h  = gethostbyname(str);
    if (h) {
        std::cout << "Name: " << h->h_name << std::endl;
        std::cout << "Aliases: " ;
        for (int i = 0; (i < (1<<8)) && h->h_aliases[i]; i++) {
            std::cout << h->h_aliases[i];
            if (h->h_aliases[i+1]) std::cout << ", ";
        }
        std::cout << "\nType: " << h->h_addrtype << std::endl;
        std::cout << "Length: " << h->h_length << std::endl;
        std::cout << "List Of Addresses: " ;
        for (int i = 0; (i < h->h_length && h->h_addr_list[i]); i++) {
            stringstream ss;
            char *s = h->h_addr_list[i];
            ss << ((int)(s[0]&0xff)) << "." << ((int)(s[1]&0xff)) << "." << ((int)(s[2]&0xff)) << "." << ((int)(s[3]&0xff));
            std::cout << ss.str() ;
            v.push_back(ss.str());
        }
        std::cout << std::endl;
    }
    return;
}

tcpServer::~tcpServer() {
    if (fd > 0) ::close(fd);
}

tcpServer::tcpServer(const char *src, int port) {
    if (src == nullptr) throw IOException("host name cannot be empty.");
    if (port < 0) throw IOException("server listen port cannot be negative.");

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) throw IOException("unable to open server socket.");
    bzero(&si_local, sizeof(si_local));
    si_local.sin_family = AF_INET;
    si_local.sin_port = htons(port);
    si_local.sin_addr.s_addr = inet_addr(src);
    bind_and_listen();
}

void tcpServer::bind_and_listen() {
    int flag = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof(flag)) != 0) {
        close(fd);
        throw IOException("setsockopt failed to SO_KEEPALIVE");
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) != 0) {
        close(fd);
        throw IOException("setsockopt failed to SO_REUSEADDR");
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag)) != 0) {
        close(fd);
        throw IOException("setsockopt failed to SO_REUSEPORT");
    }

    int fdFlags;
    if (bind(fd, (struct sockaddr *)&si_local, sizeof(si_local)) < 0) {
        close(fd);
        throw IOException("unable to bind");
    }

    if (listen(fd, 200) < 0) {
        close(fd); throw IOException("server listen error");
    }
    if ((fdFlags = fcntl(fd, F_GETFL, 0)) == -1 || fcntl(fd, F_SETFL, fdFlags | O_NONBLOCK) == -1) {
        close(fd);
        throw IOException("cannot get/set flags");
    }
}

tcpClient::tcpClient(long src, int port) {
    isconnected = true;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw IOException("unable to open TCP socket");
    bzero(&si_local, sizeof(si_local));
    si_local.sin_family = AF_INET;
    si_local.sin_port = htons(port);
    si_local.sin_addr.s_addr = src;

    int flag = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof(flag)) != 0) {
        close(fd);
        throw IOException("setsockopt failed to SO_KEEPALIVE");
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) != 0) {
        close(fd);
        throw IOException("setsockopt failed to SO_REUSEADDR");
    }

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag)) != 0) {
        close(fd);
        throw IOException("setsockopt failed to SO_REUSEPORT");
    }

    int fdFlags;

    if ((fdFlags = fcntl(fd, F_GETFL, 0)) == -1 || fcntl(fd, F_SETFL, fdFlags | O_NONBLOCK) == -1) {
        close(fd);
        throw IOException("cannot get/set flags");
    }

}

tcpClient::tcpClient(char *src, int port, bool block) : DataPipe(block) {
    isconnected = true;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        throw IOException("unable to open TCP socket");
    bzero(&si_local, sizeof(si_local));
    si_local.sin_family = AF_INET;
    si_local.sin_port = htons(port);
    si_local.sin_addr.s_addr = inet_addr(src);

    int flag = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof(flag)) != 0) {
        close(fd);
        throw IOException("setsockopt failed to SO_KEEPALIVE");
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) != 0) {
        close(fd);
        throw IOException("setsockopt failed to SO_REUSEADDR");
    }

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag)) != 0) {
        close(fd);
        throw IOException("setsockopt failed to SO_REUSEPORT");
    }

    int fdFlags;

    if (block) {
        if ((fdFlags = fcntl(fd, F_GETFL, 0)) == -1 || fcntl(fd, F_SETFL, fdFlags | O_NONBLOCK) == -1) {
            close(fd);
            throw IOException("cannot get/set flags");
        }
    }

    /*
    if (bind(fd, (struct sockaddr *)&si_local, sizeof(si_local)) < 0) {
        close(fd);
        throw IOException("unable to bind");
    }
    */
}
void tcpClient::connect(char *remote, int port) {
    std::string errMsg = "unable to connect to: ";
    bzero(&si_remote, sizeof(si_remote));
    si_remote.sin_family = AF_INET;
    si_remote.sin_addr.s_addr = inet_addr(remote);
    si_remote.sin_port = htons(port);

    int flag = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof(flag)) != 0) {
        close(fd);
        throw IOException("setsockopt failed to SO_KEEPALIVE");
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) != 0) {
        close(fd);
        throw IOException("setsockopt failed to SO_REUSEADDR");
    }

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &flag, sizeof(flag)) != 0) {
        close(fd);
        throw IOException("setsockopt failed to SO_REUSEPORT");
    }


    int rc = ::connect(fd, (struct sockaddr *)&si_remote, sizeof(si_remote)); 
    if (rc == 0 || errno == EINPROGRESS || errno == EAGAIN)
        return;
    std::cerr<< "tcpClient::connect(" << remote << ":" << port << "): " << strerror(errno) << std::endl;
    close(fd);
    errMsg.append(remote);
    isconnected = false;
    throw IOException(errMsg.c_str());
}

void tcpClient::connect(long remote, int port) {
    std::string errMsg = "unable to connect to: ";
    bzero(&si_remote, sizeof(si_remote));
    si_remote.sin_family = AF_INET;
    si_remote.sin_addr.s_addr = remote; /*inet_addr(remote);*/
    si_remote.sin_port = htons(port);

    int rc = ::connect(fd, (struct sockaddr *)&si_remote, sizeof(si_remote)); 
    if (rc == 0 || errno == EINPROGRESS || errno == EAGAIN)
        return;
    close(fd);
    //errMsg.append(remote);
    isconnected = false;
    throw IOException(errMsg.c_str());
}

int tcpClient::net_read(unsigned char *pBuffer, size_t len) {
    if (fd <= 0) return 0;

    size_t rc = read(fd, pBuffer, len);
    if (rc < 0) {
        if (rc != -EAGAIN) {
            close(fd);
            throw IOException("unable to read.");
        }
    }
    return rc;
}

int tcpClient::net_write(unsigned char *pBufer, size_t len) {
    if (fd <= 0) return 0;
    size_t rc = write(fd, pBufer, len);
    if (rc < 0) {
        if (rc != -EAGAIN) {
            close(fd);
            throw IOException("unable to write.");
        }
    }
    return rc;
}

tcpClient::~tcpClient() { std::cout << "tcpClient dtor" << std::endl; ::close(fd); fd = -1; }

int tcpClient::getfd() const { return fd; }

udpClient::udpClient(char *src, int sport, bool block) : DataPipe(block) {
    if ((fd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
        throw IOException("unable to open UDP socket");
    }
    int fdFlags = 1, incoming = 0;
    if (blocking) {
        if ((fdFlags = fcntl(fd, F_GETFL, 0)) == -1 || fcntl(fd, F_SETFL, fdFlags | O_NONBLOCK) == -1)
            throw IOException("cannot get/set flags\n");
    }

    bzero(&si_local, sizeof(si_local));
    si_local.sin_family = AF_INET;
    si_local.sin_port = htons(sport);
    si_local.sin_addr.s_addr = inet_addr(src);

    int rsize = 0xffff;
    if (bind(fd, (struct sockaddr *)&si_local, sizeof(si_local)) < 0)
        throw IOException("bind error");
    if (setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &rsize, sizeof(rsize)) == -1) {
        close (fd);
        throw IOException("Can't set GTP Receive UDP buffer size");
    }
    int wsize = 0xffff;
    if (setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &wsize, sizeof(wsize)) == -1) {
        close(fd);
        throw IOException("Can't set GTP Send UDP buffer size");
    }
}

int udpClient::getfd() { return fd; }

udpClient::~udpClient() {
    close(fd);
    fd = -1;
}

void DataPipe::disableOutput(struct pollfd* p) {
    assert(p->events & POLLOUT);
    p->events &= ~POLLOUT;
}

void DataPipe::enableOutput(struct pollfd* p) {
    assert((p->events & POLLOUT) == 0);
    p->events |= POLLOUT;
}

void DataPipe::disableInput(struct pollfd* p) {
    assert(p->events & (POLLIN|POLLPRI));
    p->events &= ~(POLLIN|POLLPRI);
}

void DataPipe::enableInput(struct pollfd* p) {
    assert((p->events & (POLLIN|POLLPRI)) == 0);
    p->events |= POLLIN|POLLPRI;
}

int udpClient::net_read(unsigned char *pBuffer, size_t len, char *remote, int rport) {
    struct sockaddr_in si_remote;
    socklen_t addrlen = sizeof (struct sockaddr_in);
    bzero(&si_remote, sizeof(si_remote));
    si_remote.sin_family = AF_INET;
    si_remote.sin_port = htons(rport);
    si_remote.sin_addr.s_addr = inet_addr(remote);

    int ret = recvfrom(fd, pBuffer, len, 0, (struct sockaddr*) &si_remote, &addrlen);
    //if (ret != -EAGAIN) throw IOException("read failed");
    //if (ret != 0 && ret != -ECONNRESET && ret != -EAGAIN && ret != -ECONNREFUSED) std::cerr << "Unexpected read error " << strerror(errno) << "\n";
    return ret;
}


int udpClient::net_write(unsigned char *pBuffer, size_t len, char *remote, int rport) {
    struct sockaddr_in si_remote;
    bzero(&si_remote, sizeof(si_remote));
    si_remote.sin_family = AF_INET;
    si_remote.sin_port = htons(rport);
    si_remote.sin_addr.s_addr = inet_addr(remote);
    if (sendto(fd, pBuffer, len, 0, (struct sockaddr *)&si_remote, sizeof(si_remote)) < 0) {
        throw IOException("sento failed");
    }
}
