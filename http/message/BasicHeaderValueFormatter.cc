#include "HttpException.h"
#include "CharArrayBuffer.h"
#include "HeaderElement.h"
#include "NameValuePair.h"
#include "HeaderValueFormatter.h"
#ifndef BASICHEADERVALUEFORMATTER_H
#include "BasicHeaderValueFormatter.h"
#endif
BasicHeaderValueFormatter  BasicHeaderValueFormatter::DEFAULT;
std::string BasicHeaderValueFormatter::SEPARATORS(" ;,:@()<>\\\"/[]?={}\t");
std::string BasicHeaderValueFormatter::UNSAFE_CHARS("\"\\");
int BasicHeaderValueFormatter::estimateElementsLen(vector<HeaderElement*> &elems) {
    if (elems.size() == 0) return 0;
    int result = (elems.size() - 1) *2;
    for (int i = 0; i < elems.size(); i++) result += estimateHeaderElementLen(elems[i]);
    return result;
}
int BasicHeaderValueFormatter::estimateHeaderElementLen(HeaderElement *elem) {
    int result = elem->getName().length();
    std::string value = elem->getValue();
    if (value.length()) result += 3 + value.length();
    int parcnt = elem->getParameterCount();
    if (parcnt > 0) {
        for (int i=0; i<parcnt; i++) result += 2 +  estimateNameValuePairLen(elem->getParameter(i));
    }
    return result;
}
int BasicHeaderValueFormatter::estimateParametersLen(vector<NameValuePair*> &nvps) {
    if (nvps.size() == 0) return 0;
    int result = (nvps.size() - 1) *2;
    for (int i = 0; i < nvps.size(); i++) result += estimateNameValuePairLen(nvps[i]);
    return result;
}
int BasicHeaderValueFormatter::estimateNameValuePairLen(NameValuePair *nvp) {
    int result = nvp->getName().length();
    std::string value = nvp->getValue();
    if (value.length()) result += 3 + value.length();
    return result;
}
void BasicHeaderValueFormatter::doFormatValue(CharArrayBuffer &buffer, std::string &value, bool quote) {
    if (!quote) for (int i = 0; (i < value.length()) && !quote; i++) quote = isSeparator(value[i]);
    if (quote) buffer.append('"');
    for (int i = 0; i < value.length(); i++) {
        char ch = value[i];
        if (isUnsafe(ch)) buffer.append('\\');
        buffer.append(ch);
    }
    if (quote) buffer.append('"');
}
std::string BasicHeaderValueFormatter::formatElements(vector<HeaderElement*> &elems, bool quote, HeaderValueFormatter *formatter) {
    if (formatter == NULL) formatter = &(BasicHeaderValueFormatter::DEFAULT);
    CharArrayBuffer buffer(8);
    return formatter->formatElements(buffer, elems, quote).toString();
}
CharArrayBuffer& BasicHeaderValueFormatter::formatElements(CharArrayBuffer &buffer, vector<HeaderElement*> &elems, bool quote) {
    if (elems.size() == 0) throw IllegalArgumentException("Header element array must not be null.");
    int len = estimateElementsLen(elems);
    buffer.ensureCapacity(len);
    for (int i=0; i<elems.size(); i++) {
        if (i > 0) buffer.append(", ");
        formatHeaderElement(buffer, elems[i], quote);
    }
    return buffer;
}
std::string BasicHeaderValueFormatter::formatHeaderElement(HeaderElement *elems, bool quote, HeaderValueFormatter *formatter) {
    if (formatter == NULL) formatter = &(BasicHeaderValueFormatter::DEFAULT);
    CharArrayBuffer buffer(8);
    return formatter->formatHeaderElement(buffer, elems, quote).toString();
}
CharArrayBuffer& BasicHeaderValueFormatter::formatHeaderElement(CharArrayBuffer &buffer, HeaderElement *elem, bool quote) {
    int len = estimateHeaderElementLen(elem);
    buffer.ensureCapacity(len);
    buffer.append(elem->getName().c_str());
    std::string value = elem->getValue();
    buffer.append('=');
    doFormatValue(buffer, value, quote);
    int parcnt = elem->getParameterCount();
    if (parcnt > 0)
        for (int i=0; i<parcnt; i++) {
            buffer.append("; ");
            formatNameValuePair(buffer, elem->getParameter(i), quote);
        }
    return buffer;
}
std::string BasicHeaderValueFormatter::formatParameters(vector<NameValuePair*> &nvps,bool quote, HeaderValueFormatter *formatter) {
    if (formatter == NULL) formatter = &(BasicHeaderValueFormatter::DEFAULT);
    CharArrayBuffer buffer(8);
    return formatter->formatParameters(buffer, nvps, quote).toString();
}
CharArrayBuffer& BasicHeaderValueFormatter::formatParameters(CharArrayBuffer &buffer, std::vector<NameValuePair*> &nvps, bool quote) {
    int len = estimateParametersLen(nvps);
    buffer.ensureCapacity(len);
    for (int i = 0; i < nvps.size(); i++) {
        if (i > 0) buffer.append("; ");
        formatNameValuePair(buffer, nvps[i], quote);
    }
    return buffer;
}
std::string BasicHeaderValueFormatter::formatNameValuePair(NameValuePair *nvp, bool quote, HeaderValueFormatter *formatter) {
    if (formatter == NULL) formatter = &(BasicHeaderValueFormatter::DEFAULT);
    CharArrayBuffer buffer(8);
    return formatter->formatNameValuePair(buffer, nvp, quote).toString();
}
CharArrayBuffer& BasicHeaderValueFormatter::formatNameValuePair(CharArrayBuffer &buffer, NameValuePair *nvp, bool quote) {
    int len = estimateNameValuePairLen(nvp);
    buffer.ensureCapacity(len);
    buffer.append(nvp->getName().c_str());
    std::string value = nvp->getValue();
    if (value.size() > 0) {
        buffer.append('=');
        doFormatValue(buffer, value, quote);
    }
    return buffer;
}
