#include "HttpException.h"
#ifndef ABSTRACTHTTPSERVERCONNECTION_H
#include "AbstractHttpServerConnection.h"
#endif
EntityDeserializer* AbstractHttpServerConnection::createEntityDeserializer() {
    return new EntityDeserializer(new LaxContentLengthStrategy());
}

EntitySerializer* AbstractHttpServerConnection::createEntitySerializer() {
    return new EntitySerializer(new StrictContentLengthStrategy());
}

HttpRequestFactory* AbstractHttpServerConnection::createHttpRequestFactory() {
    return new DefaultHttpRequestFactory();
}

HttpMessageParser* AbstractHttpServerConnection::createRequestParser(SessionInputBuffer* buffer, HttpRequestFactory* requestFactory, HttpParams *params) {
    return new HttpRequestParser(buffer, NULL, requestFactory, params);
}

HttpMessageWriter* AbstractHttpServerConnection::createResponseWriter(SessionOutputBuffer *buffer, HttpParams *params) {
    return new HttpRequestWriter(buffer, NULL, params);
}

void AbstractHttpServerConnection::init(SessionInputBuffer* ibuffer, SessionOutputBuffer *obuffer, HttpParams *params) {
    if (ibuffer == NULL) throw IllegalArgumentException("Input session buffer may not be null");
    if (obuffer == NULL) throw IllegalArgumentException("Output session buffer may not be null");
    inbuffer = ibuffer;
    outbuffer = obuffer;
    requestParser = createRequestParser(inbuffer, createHttpRequestFactory(), params);
    responseWriter = createRequestWriter(outbuffer, params);
}

AbstractHttpServerConnection::AbstractHttpServerConnection()  {
    entityserializer = createEntitySerializer();
    entitydeserializer = createEntityDeserializer();
}

bool AbstractHttpServerConnection::isRequestAvailable(int timeout) throw(IOException) {
    assertOpen();
    return inbuffer->isDataAvailable(timeout);
}

void AbstractHttpServerConnection::sendResponseHeader(HttpResponse* response) throw (HttpException, IOException) {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    assertOpen();
    responseWriter->write(response);
}

void AbstractHttpServerConnection::sendResponseEntity(HttpResponse *response) throw (HttpException, IOException) {
    if (response == NULL) throw IllegalArgumentException("HTTP request may not be null");
    if (resposne->getEntity() == NULL) return;
    entityserializer->serialize(outbuffer, response, response->getEntity());
}

void AbstractHttpServerConnection::doFlush() throw(IOException) {
    outbuffer->flush();
}

void AbstractHttpServerConnection::flush() throw(IOException) {
    assertOpen();
    doFlush();
}

HttpRequest* AbstractHttpServerConnection::receiveRequestHeader() throw (HttpException, IOException) {
    assertOpen();
    HttpRequest* request = reinterpret_cast<HttpRequest *>(requestParser->parse());
    return request;
}

void AbstractHttpServerConnection::receiveRequestEntity(HttpEntityEnclosingRequest *request) throw (HttpException, IOException) {
    if (request == NULL) throw IllegalArgumentException("HTTP response may not be null");
    assertOpen();
    HttpEntity *entity = entitydeserializer->deserialize(inbuffer, request);
    request->setEntity(entity);
}

bool AbstractHttpServerConnection::isStale() {
    assertOpen();
    try {
        inbuffer->isDataAvailable(1);
    } catch (const IOException &ex) {
        return true;
    }
    return false;
}
