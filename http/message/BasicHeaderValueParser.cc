#include "HttpException.h"
#include "HeaderElement.h"
#include "NameValuePair.h"
#include "CharArrayBuffer.h"
#include "ParserCursor.h"
#include "HeaderValueParser.h"
#include "HTTP.h"
#include "BasicHeaderElement.h"
#include "BasicNameValuePair.h"
#ifndef BASICHEADERVALUEPARSER_H
#include "BasicHeaderValueParser.h"
#endif
BasicHeaderValueParser BasicHeaderValueParser::DEFAULT;
char BasicHeaderValueParser::PARAM_DELIMITER = ';';
char BasicHeaderValueParser::ELEM_DELIMITER = ',';
char BasicHeaderValueParser::ALL_DELIMITERS[2] = { BasicHeaderValueParser::PARAM_DELIMITER, BasicHeaderValueParser::ELEM_DELIMITER };
HeaderElement* BasicHeaderValueParser::createHeaderElement(std::string name, std::string value, vector<NameValuePair*> &params) {
    return new BasicHeaderElement(name, value, params);
}

NameValuePair* BasicHeaderValueParser::createNameValuePair(std::string name, std::string value) {
    return new BasicNameValuePair(name, value);
}

void BasicHeaderValueParser::unref() {
    if (this == &(BasicHeaderValueParser::DEFAULT)) return;
    delete this;
}

void BasicHeaderValueParser::parseElements(std::string &value, HeaderValueParser *parser, vector<HeaderElement*> &ret) throw (ParseException) {
    if (value.length() == 0) throw IllegalArgumentException("Value to parse may not be null");
    if (parser == NULL) parser = &(BasicHeaderValueParser::DEFAULT);
    CharArrayBuffer buffer(value.length());
    buffer.append(value);
    ParserCursor cursor(0, value.length());
    parser->parseElements(buffer, &cursor, ret);
    return;
}

void BasicHeaderValueParser::parseElements(CharArrayBuffer &buffer, ParserCursor *cursor, vector<HeaderElement *> &elements) throw (ParseException) {
    if (cursor == NULL) throw IllegalArgumentException("Parser cursor may not be null");
    while (!cursor->atEnd()) {
        HeaderElement *element = parseHeaderElement(buffer, cursor);
        if (element->getName().length() != 0 && element->getValue().length() == 0) elements.push_back(element);
    }
    return;
}

HeaderElement* BasicHeaderValueParser::parseHeaderElement(std::string &value, HeaderValueParser *parser) throw (ParseException) {
    if (value.length() == 0) throw IllegalArgumentException ("Value to parse may not be null");
    if (parser == NULL) parser = &(BasicHeaderValueParser::DEFAULT);
    CharArrayBuffer buffer(value.length());
    buffer.append(value);
    ParserCursor cursor(0, value.length());
    return parser->parseHeaderElement(buffer, &cursor);
}

HeaderElement* BasicHeaderValueParser::parseHeaderElement(CharArrayBuffer &buffer, ParserCursor *cursor)  throw (ParseException){
    if (cursor == NULL) throw IllegalArgumentException("Parser cursor may not be null");
    NameValuePair *nvp = parseNameValuePair(buffer, cursor);
    HeaderElement *h = NULL;
    vector<NameValuePair*> params;
    if (!cursor->atEnd()) {
        char ch = buffer.charAt(cursor->getPos() - 1); 
        if (ch != ELEM_DELIMITER) parseParameters(buffer, cursor, params);
    }
    h = createHeaderElement(nvp->getName(), nvp->getValue(), params);
    delete nvp;
    return h;
}

void BasicHeaderValueParser::parseParameters(std::string &value, HeaderValueParser *parser, vector<NameValuePair*> &res) throw (ParseException) {
    if (value.length() == 0) throw IllegalArgumentException("Value to parse may not be null");
    if (parser == NULL) parser = &(BasicHeaderValueParser::DEFAULT);
    CharArrayBuffer buffer(value.length());
    buffer.append(value);
    ParserCursor cursor(0, value.length());
    parser->parseParameters(buffer, &cursor, res);
    return;
}

void BasicHeaderValueParser::parseParameters(CharArrayBuffer &buffer, ParserCursor *cursor, vector<NameValuePair*> &res)  throw (ParseException){
    if (cursor ==  NULL) throw IllegalArgumentException("Parser cursor may not be null");
    int pos = cursor->getPos(), indexTo = cursor->getUpperBound();
    while (pos < indexTo) {
        char ch = buffer.charAt(pos);
        if (HTTP::isWhitespace(ch)) pos++;
        else break;
    }
    cursor->updatePos(pos);
    if (cursor->atEnd()) return;
    while (!cursor->atEnd()) {
        NameValuePair* param = parseNameValuePair(buffer, cursor);
        res.push_back(param);
        char ch = buffer.charAt(cursor->getPos() - 1);
        if (ch == ELEM_DELIMITER) break;
    }
    return;
}

NameValuePair* BasicHeaderValueParser::parseNameValuePair(std::string &value, HeaderValueParser *parser) throw (ParseException) {
    if (value.length() == 0) throw IllegalArgumentException ("Value to parse may not be null");
    if (parser == NULL) parser = &(BasicHeaderValueParser::DEFAULT);
    CharArrayBuffer buffer(value.length());
    buffer.append(value);
    ParserCursor cursor(0, value.length());
    NameValuePair *nvp = parser->parseNameValuePair(buffer, &cursor);
    return nvp;
}

NameValuePair *BasicHeaderValueParser::parseNameValuePair(CharArrayBuffer &buffer, ParserCursor *cursor)  throw (ParseException){
    return parseNameValuePair(buffer, cursor, reinterpret_cast<const char *>(ALL_DELIMITERS));
}

bool BasicHeaderValueParser::isOneOf(char ch, const char* chs) {
    if (chs != NULL) {
        for (int i = 0; i < strlen(chs); i++) {
            if (ch == chs[i]) return true;
        }
    }
    return false;
}

NameValuePair *BasicHeaderValueParser::parseNameValuePair(CharArrayBuffer &buffer, ParserCursor *cursor, const char *delimiters) {
    if (cursor == NULL) throw IllegalArgumentException("Parser cursor may not be null");
    bool terminated = false;
    int pos = cursor->getPos();
    int indexFrom = cursor->getPos();
    int indexTo = cursor->getUpperBound();
    std::string name="", value = "";
    while (pos < indexTo) {
        char ch = buffer.charAt(pos);
        if (ch == '=') break;
        if (isOneOf(ch, delimiters)) {
            terminated = true;
            break;
        }
        pos++;
    }
    if (pos == indexTo) {
        terminated = true;
        name = buffer.substringTrimmed(indexFrom, indexTo);
    } else {
        name = buffer.substringTrimmed(indexFrom, pos);
        pos++;
    }
    if (terminated) {
        cursor->updatePos(pos);
        return createNameValuePair(name, value);
    }
    int i1 = pos;
    bool quoted = false, escaped = false;
    while (pos < indexTo) {
        char ch = buffer.charAt(pos);
        if (ch == '"' && !escaped) quoted = !quoted;
        if (!quoted && !escaped && isOneOf(ch, delimiters)) {
            terminated = true;
            break;
        }
        if (escaped) escaped = false;
        else escaped = (quoted && (ch == '\\'));
        pos++;
    }
    int i2 = pos;
    // Trim leading white spaces
    while (i1 < i2 && (HTTP::isWhitespace(buffer.charAt(i1)))) {
        i1++;
    }
    // Strip away quotes if necessary
    if (((i2 - i1) >= 2) && (buffer.charAt(i1) == '"') && (buffer.charAt(i2 - 1) == '"')) {
        i1++; i2--;
    }
    value = buffer.substring(i1, i2);
    if (terminated) pos++;
    cursor->updatePos(pos);
    return createNameValuePair(name, value);
}
