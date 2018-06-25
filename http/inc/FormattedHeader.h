#include "HttpException.h"
#ifndef FORMATTEDHEADER_H
#define FORMATTEDHEADER_H
class FormattedHeader : public Header {
    public:
    virtual ~FormattedHeader ()  { }
    virtual CharArrayBuffer getBuffer() = 0;
    virtual int getValuePos() = 0;
};
#endif
