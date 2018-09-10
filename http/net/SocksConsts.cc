#include "HttpException.h"
#ifndef SOCKSCONSTS_H
#include "SocksConsts.h"
#endif
int SocksConsts::PROTO_VERS4 = 4;
int SocksConsts::PROTO_VERS  = 5;;
int SocksConsts::DEFAULT_PORT = 1080;
int SocksConsts::NO_AUTH            = 0;
int SocksConsts::GSSAPI             = 1;
int SocksConsts::USER_PASSW         = 2;
int SocksConsts::NO_METHODS         = -1;

int SocksConsts::CONNECT            = 1;
int SocksConsts::BIND                       = 2;
int SocksConsts::UDP_ASSOC          = 3;

int SocksConsts::IPV4                       = 1;
int SocksConsts::DOMAIN_NAME                = 3;
int SocksConsts::IPV6                       = 4;

int SocksConsts::REQUEST_OK         = 0;
int SocksConsts::GENERAL_FAILURE    = 1;
int SocksConsts::NOT_ALLOWED                = 2;
int SocksConsts::NET_UNREACHABLE    = 3;
int SocksConsts::HOST_UNREACHABLE   = 4;
int SocksConsts::CONN_REFUSED               = 5;
int SocksConsts::TTL_EXPIRED                = 6;
int SocksConsts::CMD_NOT_SUPPORTED  = 7;
int SocksConsts::ADDR_TYPE_NOT_SUP  = 8;
