#include "HttpException.h"
#ifndef ENTITY_SERIALIZER_H
#define ENTITY_SERIALIZER_H
class EntitySerializer {
    private:
        ContentLengthStrategy *lenStrategy;
    protected:
        ostream& doSerialize(SessionOutputBuffer*, HttpMessage*) throws HttpException, IOException;
    public:
        EntitySerializer(ContentLengthStrategy *);
        void serialize(SessionOutputBuffer*, HttpMessage*, HttpEntity*) throws HttpException, IOException;
};
#endif
