#include "HttpException.h"
#ifndef ENGLISHREASONPHRASECATALOG_H
#define ENGLISHREASONPHRASECATALOG_H
class EnglishReasonPhraseCatalog : public ReasonPhraseCatalog {
    static vector<vector<std::string>> REASON_PHRASES;
    protected:
        EnglishReasonPhraseCatalog();
    public:
        static EnglishReasonPhraseCatalog INSTANCE;
        std::string getReason(int status, Locale *loc) ;
        static void setReason(int status, std::string reason);
};
#endif
