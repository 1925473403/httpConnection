#include "HttpException.h"
#ifndef DEFAULTHTTPCLIENTCONNECTION_H
#define DEFAULTHTTPCLIENTCONNECTION_H
public DefaultHttpClientConnection : public SocketHttpClientConnection {
    public:
        DefaultHttpClientConnection();
        void bind(Socket *socket, HttpParams *params) throw (IOException);
        std::string toString();
};
#endif
