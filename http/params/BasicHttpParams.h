#include "HttpException.h"
#ifndef BASICHTTPPARAMS_H
#define BASICHTTPPARAMS_H
class BasicHttpParams : public AbstractHttpParams {
    private:
        unordered_map<std::string, ValueBase *> parameters;
    public:
        BasicHttpParams();
        ~BasicHttpParams();
        ValueBase *getParameter(std::string name);
        HttpParams* setParameter(std::string name, ValueBase *value);
        void setParameters(vector<std::string> &names, ValueBase *value);
        bool removeParameter(std::string name) ;
        bool isParameterSet(std::string );
        bool isParameterSetLocally(std::string );
        void copyParams(HttpParams *target);
};
#endif
