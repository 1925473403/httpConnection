#include "HttpException.h"
#include "ParserCursor.h"
#ifndef HEADERVALUEPARSER_H
#define HEADERVALUEPARSER_H
class HeaderValueParser {
    public:
        virtual ~HeaderValueParser() { }
        virtual void parseElements(CharArrayBuffer&, ParserCursor *, vector<HeaderElement *> &) throw (ParseException) =0;
        virtual HeaderElement* parseHeaderElement(CharArrayBuffer&, ParserCursor *) throw (ParseException) = 0;
        virtual void parseParameters(CharArrayBuffer&, ParserCursor *, vector<NameValuePair*> &) throw (ParseException) =0;
        virtual NameValuePair* parseNameValuePair(CharArrayBuffer&, ParserCursor *) throw (ParseException) = 0;
};
#endif
