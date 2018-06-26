#include "HttpException.h"
#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H
class HttpConnection {
    public:
        virtual ~HttpConnection() { }
        virtual void close() throw (IOException) = 0;
        virtual bool isOpen() const = 0;
        virtual bool isStale() const = 0;
        virtual void setSocketTimeout(int timeout) = 0;
        virtual int getSocketTimeout() const = 0;
        virtual void shutdown() throw (IOException) = 0;
};
#endif
