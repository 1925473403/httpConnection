#include "HttpException.h"
#include "Value.h"
#include "NameValuePair.h"
#include "HeaderElement.h"
#include "Header.h"
#include "HTTP.h"
#include "InputStream.h"
#include "ByteArrayInputStream.h"
#include "OutputStream.h"
#include "HttpEntity.h"
#include "BasicHeader.h"
#include "AbstractHttpEntity.h"
#include "ByteArrayInputStream.h"
#ifndef STRINGENTITY_H
#include "StringEntity.h"
#endif
std::string conststringentity("");
StringEntity::StringEntity(std::string &s, std::string &charset) {
    if (s.empty()) throw IllegalArgumentException("Source string may not be null");
    if (conststringentity.length() == 0) conststringentity = HTTP::DEFAULT_CONTENT_CHARSET;
    content = new byte[s.length()];
    memcpy(content, s.data(), s.length());
    contentlen = (int)s.length();
    charset = HTTP::PLAIN_TEXT_TYPE + HTTP::CHARSET_PARAM + charset;
    setContentType(charset);
}

StringEntity::~StringEntity() {
    if (content) delete[] content;
}
StringEntity::StringEntity(std::string &s) : StringEntity(s, conststringentity) {
}

InputStream* StringEntity::getContent()throw(IOException, IllegalStateException) {
    return new ByteArrayInputStream(content, contentlen);
}

void StringEntity::writeTo(OutputStream *outstream) throw(IOException) {
    if (outstream == NULL) throw IllegalArgumentException("Output stream may not be null");
    outstream->write((char *)content, contentlen, contentlen);
    //outstream->flush();
}
