#include "HttpException.h"
#include "Value.h"
#include "ProtocolVersion.h"
#include "HttpVersion.h"
#include "NameValuePair.h"
#include "HeaderElement.h"
#include "Header.h"
#include "HttpParams.h"
#include "HeaderIterator.h"
#include "HttpMessage.h"
#ifndef CONTENTLENGTHSTRATEGY_H
#include "ContentLengthStrategy.h"
#endif
int ContentLengthStrategy::IDENTITY = -1;
int ContentLengthStrategy::CHUNKED = -2;
