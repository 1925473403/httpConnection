#include "HttpException.h"
#include "Value.h"
#include "NameValuePair.h"
#include "HeaderElement.h"
#include "Header.h"
#include "ContentProducer.h"
#include "HTTP.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "HttpEntity.h"
#include "BasicHeader.h"
#include "AbstractHttpEntity.h"
#ifndef ENTITYTEMPLATE_H
#include "EntityTemplate.h"
#endif
EntityTemplate::EntityTemplate(ContentProducer *cp) :contentproducer(cp) {
    if (contentproducer == NULL) throw IllegalArgumentException("Content producer may not be null");
    cp->ref();
}
EntityTemplate::~EntityTemplate() {
    if (contentproducer) contentproducer->unref();
}
InputStream* EntityTemplate::getContent()  throw (IOException, IllegalStateException) {
    throw UnsupportedOperationException("Entity template does not implement getContent()");
}
void EntityTemplate::writeTo(OutputStream *outstream) throw (IOException) {
    if (outstream == NULL) throw IllegalArgumentException("Output stream may not be null");
    contentproducer->writeTo(outstream);
}
void EntityTemplate::consumeContent() throw (IOException) {
}
