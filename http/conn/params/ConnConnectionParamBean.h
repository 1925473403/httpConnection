#include "HttpException.h"
#ifndef CONNCONNECTIONPARAMBEAN_H
#define CONNCONNECTIONPARAMBEAN_H
class ConnConnectionParamBean : public HttpAbstractParamBean {
    public:
        ConnConnectionParamBean(HttpParam *param);
        void setMaxStatusLineGarbage (int maxStatusLineGarbage);
};
#endif
