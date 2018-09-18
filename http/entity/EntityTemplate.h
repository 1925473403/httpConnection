#ifndef ENTITYTEMPLATE_H
#define ENTITYTEMPLATE_H
class EntityTemplate : public AbstractHttpEntity {
    ContentProducer *contentproducer;
    public:
    EntityTemplate(ContentProducer *cp);
    ~EntityTemplate();
    long getContentLength() { return -1; }
    InputStream* getContent() throw (IOException, IllegalStateException) ;
    bool isRepeatable() { return true; }
    void writeTo(OutputStream *outstream) throw (IOException);
    bool isStreaming() { return true; }
    void consumeContent() throw (IOException);
};
#endif
