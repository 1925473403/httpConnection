#include "HttpException.h"
#ifndef ENTITY_SERIALIZER_H
#define ENTITY_SERIALIZER_H
class EntitySerializer {
    private:
        ContentLengthStrategy *lenStrategy;
    protected:
        ostream& doSerialize(SessionOutputBuffer*, HttpMessage*) throw(HttpException, IOException);
    public:
        EntitySerializer(ContentLengthStrategy *);
        void serialize(SessionOutputBuffer*, HttpMessage*, HttpEntity*) throw(HttpException, IOException);
};
#endif
