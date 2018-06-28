#include "HttpException.h"
#ifndef CLIENTPARAMBEAN_H
#define CLIENTPARAMBEAN_H
class ClientParamBean : public HttpAbstractParamBean {
    public:
        ClientParamBean (HttpParams* params);
        void setConnectionManagerFactoryClassName (std::string factory) 
        void setConnectionManagerFactory(ClientConnectionManagerFactory factory) 
        void setHandleRedirects (bool handle) 
        void setRejectRelativeRedirect (bool reject) 
        void setMaxRedirects (int maxRedirects) 
        void setAllowCircularRedirects (bool allow) 
        void setHandleAuthentication (bool handle) 
        void setCookiePolicy (std::string policy) 
        void setVirtualHost (HttpHost* host) 
        void setDefaultHeaders (vector <Header*> headers) 
        void setDefaultHost (HttpHost* host) 
};
#endif
