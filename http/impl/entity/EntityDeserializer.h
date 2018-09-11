#include "HttpException.h"
#include "RefCount.h"
#ifndef ENTITYDESERIALIZER_H
#define ENTITYDESERIALIZER_H
class EntityDeserializer  : public RefCount {
    private:
        ContentLengthStrategy *lenStrategy;
    public:
        EntityDeserializer(ContentLengthStrategy *l);
        BasicHttpEntity *doDeserialize(SessionInputBuffer *inbuffer, HttpMessage *message) throw(HttpException, IOException );
        HttpEntity *deserialize(SessionInputBuffer *inbuffer, HttpMessage *message) throw(HttpException, IOException );
};
#endif
