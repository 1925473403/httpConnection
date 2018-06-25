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
    ~BufferedHeader() { }
    std::string getName() { return name; }
    std::string getValue() { return buffer.substringTrimmed(valuePos, buffer.length()); }
    void getElements(vector<HeaderElement *> &) throw (ParseException);
    int getValuePos() { return valuePos; }
    CharArrayBuffer getBuffer() { return buffer; }
    std::string toString() { buffer.toString(); }
};
#endif
