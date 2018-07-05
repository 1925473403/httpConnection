#include "HttpException.h"
#ifndef DEFAULTHTTPSERVERCONNECTION_H
#define DEFAULTHTTPSERVERCONNECTION_H
class DefaultHttpServerConnection: public SocketHttpServerConnection {
    public:
        DefaultHttpServerConnection();
        void bind(Socket *sock, HttpParams* params) throw (IOException);
        std::string toString();
};
#endif
