#include "HttpException.h"
#ifndef DEFAULTEDHTTPPARAMS_H
#define DEFAULTEDHTTPPARAMS_H
class DefaultedHttpParams : public AbstractHttpParams {
    HttpParams *local;
    HttpParams *defaults;
    public:
    DefaultedHttpParams(HttpParams* local,  HttpParams* defaults);
    HttpParams* copy();
    ValueBase *getParameter(std::string name);
    bool removeParameter(std::string name);
    HttpParams* setParameter(std::string name, ValueBase *value);
    HttpParams* getDefaults();
};
#endif
