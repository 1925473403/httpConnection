#include "HttpException.h"
#ifndef CLIENTPNAMES_H
#include "ClientPNames.h"
#endif
std::string ClientPNames::CONNECTION_MANAGER_FACTORY_CLASS_NAME = "http.connection-manager.factory-class-name";
std::string ClientPNames::CONNECTION_MANAGER_FACTORY = "http.connection-manager.factory-object";
std::string ClientPNames::HANDLE_REDIRECTS = "http.protocol.handle-redirects";
std::string ClientPNames::REJECT_RELATIVE_REDIRECT = "http.protocol.reject-relative-redirect";
std::string ClientPNames::MAX_REDIRECTS = "http.protocol.max-redirects";
std::string ClientPNames::ALLOW_CIRCULAR_REDIRECTS = "http.protocol.allow-circular-redirects";
std::string ClientPNames::HANDLE_AUTHENTICATION = "http.protocol.handle-authentication";
std::string ClientPNames::COOKIE_POLICY = "http.protocol.cookie-policy";
std::string ClientPNames::VIRTUAL_HOST = "http.virtual-host";
std::string ClientPNames::DEFAULT_HEADERS = "http.default-headers";
std::string ClientPNames::DEFAULT_HOST = "http.default-host";
