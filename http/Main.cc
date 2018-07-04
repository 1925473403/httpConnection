#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <pthread.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <iterator>
#include <typeinfo>

#ifndef BYTEARRAYBUFFER_H
#include "ByteArrayBuffer.h"
#endif
#ifndef CHARARRAYBUFFER_H
#include "CharArrayBuffer.h"
#endif
#include "HttpException.h"
#include "Integer.h"
#include "StringUtils.h"
#include "Value.h"
#include "HttpContext.h"
#include "BasicHttpContext.h"
#include "DefaultedHttpContext.h"
#include "ExecutionContext.h"
#include "SyncBasicHttpContext.h"
#include "ProtocolVersion.h"
#include "HttpVersion.h"
#include "HttpHost.h"
#include "Header.h"
#include "RequestLine.h"
#include "BasicRequestLine.h"
#include "HttpParams.h"
#include "AbstractHttpParams.h"
#include "HeaderIterator.h"
#include "BasicListHeaderIterator.h"
#include "HeaderElement.h"
#include "FormattedHeader.h"
#include "NameValuePair.h"
#include "CharArrayBuffer.h"
#include "ParserCursor.h"
#include "HeaderValueParser.h"
#include "HTTP.h"
#include "BasicHeaderElement.h"
#include "BasicNameValuePair.h"
#include "BasicHeaderValueParser.h"
#include "HeaderGroup.h"
#include "HttpMessage.h"
#include "AbstractHttpMessage.h"
#include "StatusLine.h"
#include "LineParser.h"
#include "BasicStatusLine.h"
#include "BasicLineParser.h"
#include "BufferedHeader.h"
#include "HttpDateGenerator.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include "NameResolver.h"
#include "InetSocketAddress.h"
#include "URI.h"
#include "URL.h"
#include "URLStreamHandler.h"
#include "URLStreamHandlerFactory.h"
#include "HttpHandler.h"
#include "FtpHandler.h"
#include "HttpsHandler.h"
#include "UriPatternMatcher.h"
#include "HttpClientParams.h"
using namespace std;

int main() {
    HttpVersion *h = HttpVersion::HTTP_1_0;
    std::cout << h->toString() << std::endl;
    h->unref();
    std::cout << typeid(h).name() << ": " << h->toString() << std::endl;
    ProtocolVersion p("http", 1, 1);
    BasicRequestLine b("GET", "http://google.com", &p);
    std::cout << b.toString() << std::endl;
    HttpDateGenerator DATE_GENERATOR ;
    std::cout << "date: " << DATE_GENERATOR.getCurrentDate() << std::endl;
    //std::string URISTR("abc://admin:admin@geeksforgeeks.org:1234/path/data?key=value&key2=value2#fragid1");
    std::cout << "Enter URI (eg: https://www.google.com/search?q=pure+virtual+function&ie=utf-8&oe=utf-8&client=firefox-b-1-ab) ";
    std::string URISTR("https://www.google.com/search?q=pure+virtual+function&ie=utf-8&oe=utf-8&client=firefox-b-1-ab");
    //std::string URISTR;
    //cin >> URISTR;
    {
        URL u(URISTR);
        std::cout << "\nhost: " << u.getHost() << "\nport: " << u.getPort() << "\nUserInfo: " << u.getUserInfo() << "\nAuthority: " << u.getAuthority() << "\nFile: " << u.getFile() << "\nRef: " << u.getRef() << "\nProtocol: " << u.getProtocol() << "\nExternalForm: " << u.toExternalForm() << std::endl;
    }
    URI uri(URISTR);
    URI uriBase("http://www.somedomain.com/");
    
    std::cout << "scheme: " << uri.getScheme() 
              << "\nauthority: " << uri.getAuthority() 
              << "\npath: " << uri.getPath()
              << "\nquery: " << uri.getQuery()
              << "\nfragment: " << uri.getFragment()
              << "\nUser Info: " << uri.getUserInfo()
              << "\nURI is absolute: " << ((uri.isAbsolute())? "TRUE" : "FALSE") 
              << "\nURI is opaque: " << ((uri.isOpaque())? "TURE" : "FALSE") << std::endl;
    
    URI uriResolved = uriBase.resolve (uri);
    std::cout << "Resolved URI = " << uriResolved.toString () << std::endl;
    URI uriRelativized = uriBase.relativize (uriResolved);
    std::cout << "Relativized URI = " << uriRelativized.toString () << std::endl;
    return 0;
}
