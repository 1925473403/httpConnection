#include <iostream>
#include <string>
using namespace std;
#ifndef EXECUTIONCONTEXT_H
#include "ExecutionContext.h"
#endif
std::string ExecutionContext::HTTP_CONNECTION("http.connection") ;
std::string ExecutionContext::HTTP_REQUEST ("http.request");
std::string ExecutionContext::HTTP_RESPONSE ("http.response");
std::string ExecutionContext::HTTP_TARGET_HOST ("http.target_host");
std::string ExecutionContext::HTTP_PROXY_HOST ("http.proxy_host");
std::string ExecutionContext::HTTP_REQ_SENT ("http.request_sent");
