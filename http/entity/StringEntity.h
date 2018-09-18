#include "HttpException.h"
#ifndef STRINGENTITY_H
#define STRINGENTITY_H
class StringEntity : public AbstractHttpEntity {
    typedef unsigned char byte;
    protected:
        byte *content;
        int contentlen;
    public:
        StringEntity(std::string &s, std::string &charset) ;
        StringEntity(std::string &s) ;
        ~StringEntity();
        bool isRepeatable() { return true; }
        long getContentLength() { return contentlen; }
        InputStream* getContent()throw(IOException, IllegalStateException) ;
        void writeTo(OutputStream *outStream) throw(IOException);
        bool isStreaming() { return false; }
};
#endif
