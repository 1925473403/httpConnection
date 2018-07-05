#include "HttpException.h"
#ifndef ABSTRACTHTTPCLIENTCONNECTION_H
#include "AbstractHttpClientConnection.h"
#endif
EntityDeserializer* AbstractHttpClientConnection::createEntityDeserializer() {
    return new EntityDeserializer(new LaxContentLengthStrategy());
}

EntitySerializer* AbstractHttpClientConnection::createEntitySerializer() {
    return new EntitySerializer(new StrictContentLengthStrategy());
}

HttpResponseFactory* AbstractHttpClientConnection::createHttpResponseFactory() {
    return new DefaultHttpResponseFactory();
}

HttpMessageParser* AbstractHttpClientConnection::createResponseParser(SessionInputBuffer* buffer, HttpResponseFactory* responseFactory, HttpParams *params) {
    return new HttpResponseParser(buffer, NULL, responseFactory, params);
}

HttpMessageWriter* AbstractHttpClientConnection::createRequestWriter(SessionOutputBuffer *buffer, HttpParams *params) {
    return new HttpRequestWriter(buffer, NULL, params);
}

void AbstractHttpClientConnection::init(SessionInputBuffer* ibuffer, SessionOutputBuffer *obuffer, HttpParams *params) {
    if (ibuffer == NULL) throw IllegalArgumentException("Input session buffer may not be null");
    if (obuffer == NULL) throw IllegalArgumentException("Output session buffer may not be null");
    inbuffer = ibuffer;
    outbuffer = obuffer;
    responseParser = createResponseParser(inbuffer, createHttpResponseFactory(), params);
    requestWriter = createRequestWriter(outbuffer, params);
}

AbstractHttpClientConnection::AbstractHttpClientConnection()  {
    entityserializer = createEntitySerializer();
    entitydeserializer = createEntityDeserializer();
}

bool AbstractHttpClientConnection::isResponseAvailable(int timeout) throw(IOException) {
    assertOpen();
    return inbuffer->isDataAvailable(timeout);
}

void AbstractHttpClientConnection::sendRequestHeader(HttpRequest* request) throw (HttpException, IOException) {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    assertOpen();
    requestWriter->write(request);
}

void AbstractHttpClientConnection::sendRequestEntity(HttpEntityEnclosingRequest* request) throw (HttpException, IOException) {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    assertOpen();
    if (request->getEntity() == NULL) return;
    entityserializer->serialize(outbuffer, request, request->getEntity());
}

void AbstractHttpClientConnection::doFlush() throw(IOException) {
    outbuffer->flush();
}

void AbstractHttpClientConnection::flush() throw(IOException) {
    assertOpen();
    doFlush();
}

HttpResponse* AbstractHttpClientConnection::receiveResponseHeader() throw (HttpException, IOException) {
    assertOpen();
    HttpResponse* response = reinterpret_cast<HttpResponse *>(responseParser->parse());
    return response;
}

void AbstractHttpClientConnection::receiveResponseEntity(HttpResponse *response) throw (HttpException, IOException) {
    if (response == NULL) throw IllegalArgumentException("HTTP response may not be null");
    assertOpen();
    HttpEntity *entity = entitydeserializer->deserialize(inbuffer, response);
    response->setEntity(entity);
}

bool AbstractHttpClientConnection::isStale() {
    if (!isOpen()) return true;
    try {
        SocketInputBuffer* ibuf = dynamic_cast<SocketInputBuffer*>(inbuffer);
        if (ibuf != NULL) {
            return ibuf->isStale();
        }
        inbuffe->isDataAvailable(1);
    } catch (const IOException &ex) {
        return true;
    }
    return false;
}
