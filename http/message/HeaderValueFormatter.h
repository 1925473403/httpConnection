#include "HttpException.h"
#ifndef HEADERVALUEFORMATTER_H
#define HEADERVALUEFORMATTER_H
class HeaderValueFormatter {
    public:
        virtual ~HeaderValueFormatter () { }
        virtual CharArrayBuffer& formatElements(CharArrayBuffer&, vector<HeaderElement*> &, bool quote) = 0;
        virtual CharArrayBuffer& formatHeaderElement(CharArrayBuffer &buffer, HeaderElement *, bool quote) = 0;
        virtual CharArrayBuffer& formatParameters(CharArrayBuffer &, std::vector<NameValuePair*> &nvps, bool quote) = 0;
        virtual CharArrayBuffer& formatNameValuePair(CharArrayBuffer &buffer, NameValuePair *nvp, bool quote) = 0;
};
#endif
