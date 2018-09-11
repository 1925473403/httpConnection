#include "HttpException.h"
#include "Value.h"
#include "StringUtils.h"
#include "Integer.h"
#include "CharArrayBuffer.h"
#include "HttpEntity.h"
#include "ContentLengthStrategy.h"
#include "HttpMessage.h"
#include "BasicHttpEntity.h"
#include "ChunkedInputStream.h"
#include "ContentLengthInputStream.h"
#include "IdentityInputStream.h"
#include "HTTP.h"
#include "SessionInputBuffer.h"
#ifndef ENTITYDESERIALIZER_H
#include "EntityDeserializer.h"
#endif
EntityDeserializer::EntityDeserializer(ContentLengthStrategy *l) lenStrategy(l) {
    if (l == NULL) IllegalArgumentException("Content length strategy may not be null");
}
BasicHttpEntity *EntityDeserializer::doDeserialize(SessionInputBuffer *inbuffer, HttpMessage *message) throw(HttpException, IOException ) {
    BasicHttpEntity *entity = new BasicHttpEntity ();
    long len = lenStrategy->determineLength(message);
    if (len == ContentLengthStrategy::CHUNKED) {
        entity->setChunked(true);
        entity->setContentLength(-1);
        entity->setContent(new ChunkedInputStream(inbuffer));
    } else if (len == ContentLengthStrategy::IDENTITY) {
        entity->setChunked(false);
        entity->setContentLength(-1);
        entity->setContent(new IdentityInputStream(inbuffer));
    } else {
        entity->setChunked(false);
        entity->setContentLength(len);
        entity->setContent(new ChunkedInputStream(inbuffer, len));
    }
    Header *contentTypeHeader = message->getFirstHeader(HTTP::CONTENT_TYPE);
    if (contentTypeHeader != NULL) {
        entity->setContentType(contentTypeHeader);
    }
    Header *contentEncodingHeader = message->getFirstHeader(HTTP::CONTENT_ENCODING);
    if (contentEncodingHeader != NULL) entity->setContentEncoding(contentEncodingHeader);
    return entity;

}
HttpEntity *EntityDeserializer::deserialize(SessionInputBuffer *inbuffer, HttpMessage *message) throw(HttpException, IOException ) {
    if (inbuffer == NULL) throw IllegalArgumentException("Session input buffer may not be null");
    if (message == NULL) throw IllegalArgumentException("HTTP message may not be null");
    return doDeserialize(inbuffer, message);
}
