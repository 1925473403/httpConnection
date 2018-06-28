#include "HttpException.h"
#ifndef CLIENTPARAMBEAN_H
#include "ClientParamBean.h"
#endif
ClientParamBean::ClientParamBean (HttpParams* params) : HttpAbstractParamBean(params) {
}

void ClientParamBean:: setConnectionManagerFactoryClassName (std::string factory) {
    params->setParameter(ClientPNames::CONNECTION_MANAGER_FACTORY_CLASS_NAME, factory);
}

void ClientParamBean:: setConnectionManagerFactory(ClientConnectionManagerFactory factory) {
    params->setParameter(ClientPNames::CONNECTION_MANAGER_FACTORY, factory);
}

void ClientParamBean:: setHandleRedirects (bool handle) {
    params->setBooleanParameter(ClientPNames::HANDLE_REDIRECTS, handle);
}

void ClientParamBean:: setRejectRelativeRedirect (bool reject) {
    params->setBooleanParameter(ClientPNames::REJECT_RELATIVE_REDIRECT, reject);
}

void ClientParamBean:: setMaxRedirects (int maxRedirects) {
    params->setIntParameter(ClientPNames::MAX_REDIRECTS, maxRedirects);
}

void ClientParamBean:: setAllowCircularRedirects (bool allow) {
    params->setBooleanParameter(ClientPNames::ALLOW_CIRCULAR_REDIRECTS, allow);
}

void ClientParamBean:: setHandleAuthentication (bool handle) {
    params->setBooleanParameter(ClientPNames::HANDLE_AUTHENTICATION, handle);
}

void ClientParamBean:: setCookiePolicy (std::string policy) {
    params->setParameter(ClientPNames::COOKIE_POLICY, policy);
}

void ClientParamBean:: setVirtualHost (HttpHost host) {
    params->setParameter(ClientPNames::VIRTUAL_HOST, host);
}

void ClientParamBean:: setDefaultHeaders (Collection <Header> headers) {
    params->setParameter(ClientPNames::DEFAULT_HEADERS, headers);
}

void ClientParamBean:: setDefaultHost (HttpHost host) {
    params->setParameter(ClientPNames::DEFAULT_HOST, host);
}
