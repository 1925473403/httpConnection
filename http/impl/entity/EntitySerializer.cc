#include "EntitySerializer.h"
EntitySerializer::EntitySerializer(ContentLengthStrategy *lenStrategy) {
    if (lenStrategy == NULL) throw IllegalArgumentException("Content length strategy may not be null");
    this->lenStrategy = lenStrategy;
}

ostream& EntitySerializer::doSerialize(SessionOutputBuffer* outbuffer, HttpMessage *message) throws HttpException, IOException {
    long len = lenStrategy->determineLength(message);
     if (len == ContentLengthStrategy::CHUNKED) return new ChunkedOutputStream(outbuffer);
     else if (len == ContentLengthStrategy::IDENTITY) return new IdentityOutputStream(outbuffer);
     else return new ContentLengthOutputStream(outbuffer, len);
}

void EntitySerializer::serialize(SessionOutputBuffer* outbuffer, HttpMessage* message, HttpEntity* entity) throws HttpException, IOException {
    if (outbuffer == NULL) throw  IllegalArgumentException("Session output buffer may not be null");
    if (message == NULL) throw IllegalArgumentException("HTTP message may not be null");
    if (entity == NULL) throw IllegalArgumentException("HTTP entity may not be null");
    ostream os = doSerialize(outbuffer, message);
    entity.writeTo(outstream);
    outstream.close();
}
