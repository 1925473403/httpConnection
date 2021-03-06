#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include "Value.h"
#include "CharArrayBuffer.h"
#include "HTTP.h"
#include "HttpParams.h"
#include "AbstractHttpParams.h"
#include "BasicHttpParams.h"
#include "ProtocolVersion.h"
#include "HttpVersion.h"
#include "CoreProtocolPNames.h"
#include "HttpProtocolParams.h"
#include "DefaultedHttpParams.h"
#include "CoreConnectionPNames.h"
#include "HttpConnectionParams.h"
#include "HttpAbstractParamBean.h"
#include "HttpConnectionParamBean.h"

using namespace std;

int main() {
    unordered_map<int, ValueBase*> m;
    m.insert(std::make_pair(1, new Value<int>(1)));
    m.insert(std::make_pair(2, new Value<std::string>("Test")));
    m.insert(std::make_pair(3, new Value<bool>(true)));
    for (unordered_map<int, ValueBase *>::iterator it = m.begin(); it != m.end(); it++) {
        ValueBase *v = it->second;
        std::cout << it->first << " " << *v << std::endl;
        v->unref();
    }
    m.clear();
    HttpParams *params = new BasicHttpParams();
    //params->setParameter("Double", new Value<double>(6.324353));
    //params->setParameter("String", new Value<std::string>(std::string("HTTP")));
    //params->setParameter("Integer", new Value<int>(23));
    //params->setParameter("ProtocolVersion", new Value<ProtocolVersion*>(new ProtocolVersion("HTTP", 1, 0)));
 
    Value<double> vd(6.324353);
    Value<std::string> vs("HTTP");
    Value<int> vi(23);
    params->setParameter("Double", &vd);
    params->setParameter("String", &vs);
    params->setParameter("Integer", &vi);
    params->setBooleanParameter("BOOLEAN", false);
    ProtocolVersion pv("HTTP", 1, 1);
    Value<ProtocolVersion *> vpv(&pv);
    params->setParameter("ProtocolVersion", &vpv);
    std::cout << "BOOLEAN: " << params->getBooleanParameter("BOOLEAN", true) << std::endl;
    ValueBase *v = params->getParameter("ProtocolVersion");
    ProtocolVersion *p = nullptr;
    p = type_cast<ProtocolVersion *>(v, p);
    if (p) {
        std::cout << p->toString() << std::endl;
        std::cout << "cast success " << std::endl;
    } else std::cout << "cast failure" << std::endl;

    v = params->getParameter("String");
    std::string t("");
    t  = type_cast<std::string>(v, t);
    std::cout << t << std::endl;
    /*
    Value<ProtocolVersion*> *v1 = dynamic_cast<Value <ProtocolVersion *> *> (v);
    if (v1 != NULL) {
        ProtocolVersion *p = v1->value();
        std::cout << p->toString() << std::endl;
    }
    */
    HttpParams *httpParams = new DefaultedHttpParams(params, params);
    httpParams->unref();
    params->unref();
    HttpVersion::HTTP_1_0->unref();
    HttpVersion::HTTP_1_1->unref();
    HttpVersion::HTTP_0_9->unref();
    return 0;
}
