#include "HttpException.h"
#include "Cookie.h"
#ifndef CLIENTCOOKIE_H
#include "ClientCookie.h"
#endif
std::string ClientCookie::VERSION_ATTR("version");
std::string ClientCookie::PATH_ATTR("path");
std::string ClientCookie::DOMAIN_ATTR("domain");
std::string ClientCookie::MAX_AGE_ATTR("max-age");
std::string ClientCookie::SECURE_ATTR("secure");
std::string ClientCookie::COMMENT_ATTR("comment");
std::string ClientCookie::EXPIRES_ATTR("expires");
std::string ClientCookie::PORT_ATTR("port");
std::string ClientCookie::COMMENTURL_ATTR("commenturl");
std::string ClientCookie::DISCARD_ATTR("discard");
ClientCookie::~ClientCookie() { }
