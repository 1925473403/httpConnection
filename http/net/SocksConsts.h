#include "HttpException.h"
#ifndef SOCKSCONSTS_H
#define SOCKSCONSTS_H
class SocksConsts {
    public:
        virtual ~SocksConsts() { }
        static int PROTO_VERS4;
        static int PROTO_VERS;
        static int DEFAULT_PORT;
        static int NO_AUTH;
        static int GSSAPI;
        static int USER_PASSW;
        static int NO_METHODS;

        static int CONNECT;
        static int BIND;
        static int UDP_ASSOC;

        static int IPV4;
        static int DOMAIN_NAME;
        static int IPV6;

        static int REQUEST_OK;
        static int GENERAL_FAILURE;
        static int NOT_ALLOWED;
        static int NET_UNREACHABLE;
        static int HOST_UNREACHABLE;
        static int CONN_REFUSED;
        static int TTL_EXPIRED;
        static int CMD_NOT_SUPPORTED;
        static int ADDR_TYPE_NOT_SUP;

};
#endif
