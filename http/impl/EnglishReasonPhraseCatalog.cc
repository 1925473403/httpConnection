#include "HttpException.h"
#ifndef ENGLISHREASONPHRASECATALOG_H
#include "EnglishReasonPhraseCatalog.h"
#endif
vector<vector<std::string>> EnglishReasonPhraseCatalog::REASON_PHRASES(6);
EnglishReasonPhraseCatalog EnglishReasonPhraseCatalog::INSTANCE;
EnglishReasonPhraseCatalog::EnglishReasonPhraseCatalog() {
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_OK, "OK");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_CREATED, "Created");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_ACCEPTED, "Accepted");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_NO_CONTENT, "No Content");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_MOVED_PERMANENTLY, "Moved Permanently");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_MOVED_TEMPORARILY, "Moved Temporarily");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_NOT_MODIFIED, "Not Modified");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_BAD_REQUEST, "Bad Request");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_UNAUTHORIZED, "Unauthorized");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_FORBIDDEN, "Forbidden");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_NOT_FOUND, "Not Found");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_INTERNAL_SERVER_ERROR, "Internal Server Error");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_NOT_IMPLEMENTED, "Not Implemented");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_BAD_GATEWAY, "Bad Gateway");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_SERVICE_UNAVAILABLE, "Service Unavailable");

    // HTTP 1.1 Server status codes -- see RFC 2048
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_CONTINUE, "Continue");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_TEMPORARY_REDIRECT, "Temporary Redirect");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_METHOD_NOT_ALLOWED, "Method Not Allowed");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_CONFLICT, "Conflict");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_PRECONDITION_FAILED, "Precondition Failed");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_REQUEST_TOO_LONG, "Request Too Long");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_REQUEST_URI_TOO_LONG, "Request-URI Too Long");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_UNSUPPORTED_MEDIA_TYPE, "Unsupported Media Type");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_MULTIPLE_CHOICES, "Multiple Choices");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_SEE_OTHER, "See Other");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_USE_PROXY, "Use Proxy");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_PAYMENT_REQUIRED, "Payment Required");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_NOT_ACCEPTABLE, "Not Acceptable");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_PROXY_AUTHENTICATION_REQUIRED, "Proxy Authentication Required");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_REQUEST_TIMEOUT, "Request Timeout");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_SWITCHING_PROTOCOLS, "Switching Protocols");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_NON_AUTHORITATIVE_INFORMATION, "Non Authoritative Information");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_RESET_CONTENT, "Reset Content");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_PARTIAL_CONTENT, "Partial Content");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_GATEWAY_TIMEOUT, "Gateway Timeout");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_HTTP_VERSION_NOT_SUPPORTED, "Http Version Not Supported");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_GONE, "Gone");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_LENGTH_REQUIRED, "Length Required");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_REQUESTED_RANGE_NOT_SATISFIABLE, "Requested Range Not Satisfiable");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_EXPECTATION_FAILED, "Expectation Failed");

    // WebDAV Server-specific status codes
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_PROCESSING, "Processing");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_MULTI_STATUS, "Multi-Status");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_UNPROCESSABLE_ENTITY, "Unprocessable Entity");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_INSUFFICIENT_SPACE_ON_RESOURCE, "Insufficient Space On Resource");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_METHOD_FAILURE, "Method Failure");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_LOCKED, "Locked");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_INSUFFICIENT_STORAGE, "Insufficient Storage");
    EnglishReasonPhraseCatalog::setReason(HttpStatus::SC_FAILED_DEPENDENCY, "Failed Dependency");
}
std::string EnglishReasonPhraseCatalog::getReason(int status, Locale *loc) {
    if ((status < 100) || (status >= 600)) throw IllegalArgumentException(("Unknown category for status code %d.", status);
    int category = status / 100;
    int subcode  = status - 100*category;
    std::string reason = "";
    if (REASON_PHRASES[category].size() > subcode) reason = REASON_PHRASES[category][subcode];
    return reason;
}
void EnglishReasonPhraseCatalog::setReason(int status, std::string reason) {
    int category = status / 100;
    int subcode  = status - 100*category;
    REASON_PHRASES[category].push_back(reason);
}
