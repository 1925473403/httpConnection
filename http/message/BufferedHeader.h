#include "HttpException.h"
#ifndef BUFFEREDHEADER_H
#define BUFFEREDHEADER_H
class BufferedHeader : public FormattedHeader {
    private:
    std::string name;
    CharArrayBuffer buffer;
    int valuePos;
    public:
    BufferedHeader(CharArrayBuffer &b) throw (ParseException);
    std::string getName() const { return name; }
    std::string getValue() const { return buffer.substringTrimmed(valuePos, buffer.length()); }
    void getElements(vector<HeaderElement *> &) throw (ParseException);
    int getValuePos() const { return valuePos; }
    CharArrayBuffer& getBuffer() { return buffer; }
    std::string toString() { buffer.toString(); }
};
#endif
