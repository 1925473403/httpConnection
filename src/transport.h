#include <vector>
#include <string>
#ifndef _TRANSPORT_H_
#define _TRANSPORT_H_

typedef struct host {
    void resolve(char *, std::vector<long>&);
    void resolve(char *, std::vector<std::string>&);
}host;

class DataPipe {
    protected:
    bool blocking;
    public:
        DataPipe(bool block = false):blocking(block) { }
        void disableOutput(struct pollfd* p);
        void enableOutput(struct pollfd* p);
        void disableInput(struct pollfd* p);
        void enableInput(struct pollfd* p);
};

class tcpClient:public DataPipe {
    bool isconnected;
    int fd;
    struct sockaddr_in si_local;
    struct sockaddr_in si_remote;
    public:
        bool connected() const { return isconnected; }
        tcpClient(char *src, int port, bool blocking=false);
        tcpClient(long, int port);
        ~tcpClient();
        int getfd() const;
        void setfd(int f) { fd = f; }
        void connect(char *, int rport);
        void connect(long, int rport);
        int net_read(unsigned char *pBuffer, size_t len);
        int net_write(unsigned char *pBuffer, size_t len);
};

class udpClient:public DataPipe {
    int fd;
    struct sockaddr_in si_local;
    public:
        udpClient(char *src, int port, bool blocking=false);
        ~udpClient();
        int getfd() ;
        int net_read(unsigned char *pBuffer, size_t len, char *remote, int rport);
        int net_write(unsigned char *pBuffer, size_t len, char *, int);
};


class IOException : public std::exception {
    public:
        IOException(const char *str) {
            if (str) {
                snprintf(m_reason, 511, "%s", str);
            }
        }
        const char *what() const throw() { return m_reason; }
        int describe(char *apStr, int len) {
            if ((apStr) && len > 1)
                return snprintf(apStr, len - 1, "%s", m_reason);
            return 0;
        }
    private:
        char m_reason[512];
};
class MalformedURLException : public std::exception {
    public:
        MalformedURLException(const char *str, const std::string &s) {
            snprintf(m_reason, 511, "%s %s", str, s.c_str());
        }
        const char *what() const throw() { return m_reason; }
        int describe(char *apStr, int len) {
            if ((apStr) && len > 1)
                return snprintf(apStr, len - 1, "%s", m_reason);
            return 0;
        }
    private:
        char m_reason[512];
};
#endif
