#include "Value.h"
#include "CoreProtocolPNames.h"
#include "ProtocolVersion.h"
#include "HttpVersion.h"
#include "HttpStatus.h"
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "HttpEntityEnclosingRequest.h"
#include "HttpClientConnection.h"
#ifndef HTTPREQUESTEXECUTOR_H
#include "HttpRequestExecutor.h"
#endif
bool HttpRequestExecutor::canResponseHaveBody(HttpRequest *request, HttpResponse *response) {
    if (request->getRequestLine()->getMethod() == "HEAD") return false;
    int status = response->getStatusLine()->getStatusCode();
    return status >= HttpStatus::SC_OK && status != HttpStatus::SC_NO_CONTENT && status != HttpStatus::SC_NOT_MODIFIED && status != HttpStatus::SC_RESET_CONTENT;
}
HttpResponse* HttpRequestExecutor::execute(HttpRequest* request, HttpClientConnection* conn, HttpContext* context) throws IOException, HttpException {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    if (conn == NULL) throw IllegalArgumentException("Client connection may not be null");
    if (context == NULL) throw IllegalArgumentException("HTTP context may not be null");
    try {
        HttpResponse *response = doSendRequest(request, conn, context);
        if (response == NULL) response = doReceiveResponse(request, conn, context);
        return response;
    } catch (const IOException &ex) {
        conn->close();
        throw;
    } catch (const HttpException &ex) {
        conn->close();
        throw;
    } catch (const std::exception &ex) {
        conn->close();
        throw;
    }
    return NULL;
}
void HttpRequestExecutor::preProcess(HttpRequest* request, HttpProcessor* processor, HttpContext* context) throws HttpException, IOException {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    if (processor == NULL) throw IllegalArgumentException("HTTP processor may not be null");
    if (context == NULL) throw IllegalArgumentException("HTTP context may not be null");
    processor->process(request, context);
}
HttpResponse* HttpRequestExecutor::doSendRequest(HttpRequest* request, HttpClientConnection* conn, HttpContext* context) throws IOException, HttpException {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    if (conn == NULL) throw IllegalArgumentException("Client connection may not be null");
    if (context == NULL) throw IllegalArgumentException("HTTP context may not be null");
    HttpResponse* response = NULL;
    context->setAttribute(ExecutionContext::HTTP_REQ_SENT, false);
    conn->sendRequestHeader(request);
    if (HttpEntityEnclosingRequest* v = dynamic_cast<HttpEntityEnclosingRequest *>(request)) {
        bool sendentity = true;
        ProtocolVersion *ver = v->getRequestLine().getProtocolVersion();
        if (v->expectContinue() && !ver.lessEquals(HttpVersion::HTTP_1_0)) {
            conn->flush();
            int tms = request->getParams()->getIntParameter(CoreProtocolPNames::WAIT_FOR_CONTINUE, 2000);
            if (conn->isResponseAvailable(tms)) {
                response = conn->receiveResponseHeader();
                if (canResponseHaveBody(request, response)) {
                    conn->receiveResponseEntity(response);
                }
                int status = response->getStatusLine()->getStatusCode();
                if (status < 200) {
                    if (status != HttpStatus::SC_CONTINUE) {
                        delete response;
                        throw ProtocolException("Unexpected response: %s", response->getStatusLine());
                    }
                    delete response;
                    response = NULL;
                } else sendentity = false;
            }
        }
        if (sendentity) conn->sendRequestEntity(v);
    }
    conn->flush();
    context->setAttribute(ExecutionContext::HTTP_REQ_SENT, true);
    return response;
}
HttpResponse* HttpRequestExecutor::doReceiveResponse(HttpRequest *request, HttpClientConnection* conn, HttpContext* context) throws IOException, HttpException {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    if (conn == NULL) throw IllegalArgumentException("Client connection may not be null");
    if (context == NULL) throw IllegalArgumentException("HTTP context may not be null");
    HttpResponse* response = NULL;
    int statuscode = 0;
    while (response == NULL || statuscode < HttpStatus::SC_OK) {
        response = conn->receiveResponseHeader();
        if (canResponseHaveBody(request, response)) {
            conn->receiveResponseEntity(response);
        }
        statuscode = response->getStatusLine().getStatusCode();
    }
    return response;
}
void HttpRequestExecutor::postProcess(HttpRequest* request, HttpProcessor* processor, HttpContext* context) throws HttpException, IOException {
    if (response == NULL) throw IllegalArgumentException("HTTP response may not be null");
    if (processor == NULL) throw IllegalArgumentException("HTTP processor may not be null");
    if (context == NULL) throw IllegalArgumentException("HTTP context may not be null");
    processor->process(response, context);
}
