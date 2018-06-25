#include "HttpException.h"
#ifndef BASICHEADERVALUEPARSER_H
#define BASICHEADERVALUEPARSER_H
class BasicHeaderValueParser : public HeaderValueParser {
    static BasicHeaderValueParser DEFAULT;
    static char PARAM_DELIMITER;
    static char ELEM_DELIMITER;
    static char ALL_DELIMITERS[2];
        ~BasicHeaderValueParser() { }
    protected:
        HeaderElement* createHeaderElement(std::string name, std::string value, vector<NameValuePair*> &params);
        NameValuePair* createNameValuePair(std::string name, std::string value);
    public:
        void unref();
        static void parseElements(std::string &value, HeaderValueParser *parser, vector<HeaderElement*>&) throw (ParseException);
        void parseElements(CharArrayBuffer &buffer, ParserCursor *cursor, vector<HeaderElement*> &) throw (ParseException);
        static HeaderElement* parseHeaderElement(std::string &value, HeaderValueParser *parser) throw (ParseException);
        HeaderElement* parseHeaderElement(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException);
        static void parseParameters(std::string &value, HeaderValueParser *parser, vector<NameValuePair*> &) throw (ParseException);
        void parseParameters(CharArrayBuffer &buffer, ParserCursor *cursor, vector<NameValuePair*> &) throw (ParseException);
        static NameValuePair* parseNameValuePair(std::string &value, HeaderValueParser *parser) throw (ParseException);
        NameValuePair *parseNameValuePair(CharArrayBuffer &buffer, ParserCursor *cursor) throw (ParseException);
        static bool isOneOf(char ch, const char* chs);
        NameValuePair *parseNameValuePair(CharArrayBuffer &buffer, ParserCursor *cursor, const char *delimiters);
};
#endif
