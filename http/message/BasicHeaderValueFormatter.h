#include "HttpException.h"
#ifndef BASICHEADERVALUEFORMATTER_H
#define BASICHEADERVALUEFORMATTER_H
class BasicHeaderValueFormatter : public HeaderValueFormatter {
    static std::string SEPARATORS;
    static std::string UNSAFE_CHARS;
    protected:
        int estimateElementsLen(vector<HeaderElement*> &elems); 
        int estimateHeaderElementLen(HeaderElement* elem); 
        int estimateParametersLen(vector<NameValuePair*> &nvps); 
        int estimateNameValuePairLen(NameValuePair* nvp); 
        void doFormatValue(CharArrayBuffer &buffer, std::string &value, bool quote); 
        bool isSeparator(char ch) { return SEPARATORS.find(ch) != std::string::npos; }
        bool isUnsafe(char ch) { return UNSAFE_CHARS.find(ch) != std::string::npos; }
    public:
        ~BasicHeaderValueFormatter() { }
        static BasicHeaderValueFormatter DEFAULT;
        static std::string formatElements(vector<HeaderElement*> &elems, bool quote, HeaderValueFormatter *formatter); 
        CharArrayBuffer& formatElements(CharArrayBuffer &buffer, vector<HeaderElement *> &elems, bool quote); 
        static std::string formatHeaderElement(HeaderElement* elems, bool quote, HeaderValueFormatter *formatter); 
        CharArrayBuffer& formatHeaderElement(CharArrayBuffer &buffer, HeaderElement* elem, bool quote); 
        static std::string formatParameters(vector<NameValuePair*> &nvps,bool quote, HeaderValueFormatter *formatter); 
        CharArrayBuffer& formatParameters(CharArrayBuffer &buffer, std::vector<NameValuePair*> &nvps, bool quote); 
        static std::string formatNameValuePair(NameValuePair *nvp, bool quote, HeaderValueFormatter *formatter);
        CharArrayBuffer& formatNameValuePair(CharArrayBuffer &buffer, NameValuePair *nvp, bool quote);
};
#endif
