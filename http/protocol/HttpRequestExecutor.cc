#include "HttpException.h"
#include "ByteArrayBuffer.h"
#include "CharArrayBuffer.h"
#include "Integer.h"
#include "StringUtils.h"
#include "HTTP.h"
#include "ProtocolVersion.h"
#include "HttpVersion.h"
#include "Value.h"
#include "HttpParams.h"
#include "AbstractHttpParams.h"
#include "BasicHttpParams.h"
#include "CoreProtocolPNames.h"
#include "HttpProtocolParams.h"
#include "DefaultedHttpParams.h"
#include "RequestLine.h"
#include "HttpStatus.h"
#include "NameValuePair.h"
#include "HeaderElement.h"
#include "Header.h"
#include "HeaderIterator.h"
#include "InputStream.h"
#include "OutputStream.h"
#include "StatusLine.h"
#include "HttpEntity.h"
#include "AbstractHttpEntity.h"
#include "ByteArrayEntity.h"
#include "ExecutionContext.h"
#include "HttpMessage.h"
#include "HttpContext.h"
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "HttpResponseInterceptor.h"
#include "HttpRequestInterceptor.h"
#include "HttpProcessor.h"
#include "HttpConnection.h"
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
HttpResponse* HttpRequestExecutor::execute(HttpRequest* request, HttpClientConnection* conn, HttpContext* context) throw (IOException, HttpException) {
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
void HttpRequestExecutor::preProcess(HttpRequest* request, HttpProcessor* processor, HttpContext* context)  throw (IOException, HttpException) {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    if (processor == NULL) throw IllegalArgumentException("HTTP processor may not be null");
    if (context == NULL) throw IllegalArgumentException("HTTP context may not be null");
    processor->process(request, context);
}
HttpResponse* HttpRequestExecutor::doSendRequest(HttpRequest* request, HttpClientConnection* conn, HttpContext* context) throw (IOException, HttpException) {
    if (request == NULL) throw IllegalArgumentException("HTTP request may not be null");
    if (conn == NULL) throw IllegalArgumentException("Client connection may not be null");
    if (context == NULL) throw IllegalArgumentException("HTTP context may not be null");
    HttpResponse* response = NULL;
    Value<bool> *v = new Value<bool>(false);
    context->setAttribute(ExecutionContext::HTTP_REQ_SENT, v);
    conn->sendRequestHeader(request);
    if (HttpEntityEnclosingRequest* v = dynamic_cast<HttpEntityEnclosingRequest *>(request)) {
        bool sendentity = true;
        ProtocolVersion *ver = v->getRequestLine()->getProtocolVersion();
        if (v->expectContinue() && !ver->lessEquals(*HttpVersion::HTTP_1_0)) {
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
                        std::string err("Unexpected response: ");
                        //err += response->getStatusLine();
                        throw ProtocolException(err);
                    }
                    delete response;
                    response = NULL;
                } else sendentity = false;
            }
        }
        if (sendentity) conn->sendRequestEntity(v);
    }
    conn->flush();
    Value<bool> *v1 = new Value<bool>(true);
    context->setAttribute(ExecutionContext::HTTP_REQ_SENT, v1);
    return response;
}
HttpResponse* HttpRequestExecutor::doReceiveResponse(HttpRequest *request, HttpClientConnection* conn, HttpContext* context) throw (IOException, HttpException) {
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
        statuscode = response->getStatusLine()->getStatusCode();
    }
    return response;
}
void HttpRequestExecutor::postProcess(HttpResponse* response, HttpProcessor* processor, HttpContext* context)  throw (IOException, HttpException) {
    if (response == NULL) throw IllegalArgumentException("HTTP response may not be null");
    if (processor == NULL) throw IllegalArgumentException("HTTP processor may not be null");
    if (context == NULL) throw IllegalArgumentException("HTTP context may not be null");
    processor->process(response, context);
}
