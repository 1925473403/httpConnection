#include "HttpException.h"
#ifndef ENTITYDESERIALIZER_H
#define ENTITYDESERIALIZER_H
class EntityDeserializer  {
    private:
        ContentLengthStrategy *lenStrategy;
    public:
        EntityDeserializer(ContentLengthStrategy *l);
        BasicHttpEntity *doDeserialize(SessionInputBuffer *inbuffer, HttpMessage *message) throw(HttpException, IOException );
        HttpEntity *deserialize(SessionInputBuffer *inbuffer, HttpMessage *message) throw(HttpException, IOException );
};
#endif
