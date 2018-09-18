#ifndef BASICHTTPENTITY_H
#define BASICHTTPENTITY_H
class BasicHttpEntity : public AbstractHttpEntity {
    InputStream *content;
    bool contentObtained;
    long length;
    public:
    BasicHttpEntity();
    ~BasicHttpEntity();
    long getContentLength();
    InputStream *getContent() throw(IOException, IllegalStateException);
    bool isRepeatable();
    void setContentLength(long len);
    void setContent(InputStream *instream);
    void writeTo(OutputStream *outstream) throw (IOException);
    bool isStreaming();
    void consumeContent() throw (IOException);
};
#endif
