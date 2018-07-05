#include "HttpException.h"
#ifndef CONNCONNECTIONPARAMBEAN_H
#include "ConnConnectionParamBean.h"
#endif
ConnConnectionParamBean::ConnConnectionParamBean(HttpParam *param) : HttpAbstractParamBean(param) {
}
void ConnConnectionParamBean::setMaxStatusLineGarbage (int maxStatusLineGarbage) {
    params->setIntParameter(ConnConnectionPNames::MAX_STATUS_LINE_GARBAGE, maxStatusLineGarbage);
}
