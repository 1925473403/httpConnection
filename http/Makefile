CXX=g++
CXXFLAGS=-Wall -g -m64 -std=c++11 $(INCLUDEDIRS)
LDFLAGS=-lpthread -lnsl -lresolv
INCLUDEDIRS = -I${SRC_HOME}/inc -I${SRC_HOME}/protocol -I${SRC_HOME}/util -I${SRC_HOME}/params -I${SRC_HOME}/net -I${SRC_HOME}/message -I${SRC_HOME}/client/params
SRC_HOME=/home/fworks/httpConnection/http
all:	Main
Main:	${SRC_HOME}/Main.o ${SRC_HOME}/util/StringUtils.o \
                        ${SRC_HOME}/protocol/HttpHost.o \
                        ${SRC_HOME}/protocol/HttpVersion.o \
                        ${SRC_HOME}/net/URI.o \
                        ${SRC_HOME}/net/NameResolver.o \
                        ${SRC_HOME}/net/InetSocketAddress.o \
                        ${SRC_HOME}/net/URLStreamHandler.o \
                        ${SRC_HOME}/net/HttpHandler.o \
                        ${SRC_HOME}/net/HttpsHandler.o \
                        ${SRC_HOME}/net/FtpHandler.o \
                        ${SRC_HOME}/net/URL.o \
                        ${SRC_HOME}/protocol/ProtocolVersion.o \
                        ${SRC_HOME}/util/CharArrayBuffer.o \
                        ${SRC_HOME}/util/ByteArrayBuffer.o \
                        ${SRC_HOME}/params/CoreProtocolPNames.o \
                        ${SRC_HOME}/params/HttpProtocolParams.o \
                        ${SRC_HOME}/params/AbstractHttpParams.o \
                        ${SRC_HOME}/params/BasicHttpParams.o \
                        ${SRC_HOME}/params/Value.o \
                        ${SRC_HOME}/client/params/CookiePolicy.o \
                        ${SRC_HOME}/client/params/ClientPNames.o \
                        ${SRC_HOME}/client/params/HttpClientParams.o \
                        ${SRC_HOME}/message/ParserCursor.o \
                        ${SRC_HOME}/message/BasicHeader.o \
                        ${SRC_HOME}/message/BasicHeaderValueFormatter.o \
                        ${SRC_HOME}/message/BasicHeaderValueParser.o \
                        ${SRC_HOME}/message/BasicHeaderElement.o \
                        ${SRC_HOME}/message/BasicNameValuePair.o \
                        ${SRC_HOME}/message/BasicLineFormatter.o \
                        ${SRC_HOME}/message/BasicRequestLine.o \
                        ${SRC_HOME}/message/AbstractHttpMessage.o \
                        ${SRC_HOME}/message/BasicHttpRequest.o \
                        ${SRC_HOME}/message/HeaderGroup.o \
                        ${SRC_HOME}/message/BasicListHeaderIterator.o \
                        ${SRC_HOME}/message/BasicHeaderIterator.o \
                        ${SRC_HOME}/message/BasicHeaderElementIterator.o \
                        ${SRC_HOME}/message/BufferedHeader.o \
                        ${SRC_HOME}/message/BasicStatusLine.o \
                        ${SRC_HOME}/message/BasicLineParser.o \
                        ${SRC_HOME}/protocol/HTTP.o \
                        ${SRC_HOME}/protocol/HttpContext.o \
                        ${SRC_HOME}/protocol/ExecutionContext.o \
                        ${SRC_HOME}/protocol/BasicHttpContext.o \
                        ${SRC_HOME}/protocol/DefaultedHttpContext.o \
                        ${SRC_HOME}/protocol/HttpDateGenerator.o \
                        ${SRC_HOME}/protocol/UriPatternMatcher.o \
                        ${SRC_HOME}/protocol/SyncBasicHttpContext.o
	$(CXX) $(CXXFLAGS) -o main ${SRC_HOME}/Main.o ${SRC_HOME}/util/StringUtils.o \
                        ${SRC_HOME}/protocol/HTTP.o \
                        ${SRC_HOME}/protocol/HttpHost.o \
                        ${SRC_HOME}/protocol/HttpVersion.o \
                        ${SRC_HOME}/net/URI.o \
                        ${SRC_HOME}/net/NameResolver.o \
                        ${SRC_HOME}/net/InetSocketAddress.o \
                        ${SRC_HOME}/net/URLStreamHandler.o \
                        ${SRC_HOME}/net/HttpHandler.o \
                        ${SRC_HOME}/net/HttpsHandler.o \
                        ${SRC_HOME}/net/FtpHandler.o \
                        ${SRC_HOME}/net/URL.o \
                        ${SRC_HOME}/protocol/ProtocolVersion.o \
                        ${SRC_HOME}/util/CharArrayBuffer.o \
                        ${SRC_HOME}/util/ByteArrayBuffer.o \
                        ${SRC_HOME}/params/CoreProtocolPNames.o \
                        ${SRC_HOME}/params/HttpProtocolParams.o \
                        ${SRC_HOME}/params/AbstractHttpParams.o \
                        ${SRC_HOME}/params/BasicHttpParams.o \
                        ${SRC_HOME}/params/Value.o \
                        ${SRC_HOME}/client/params/CookiePolicy.o \
                        ${SRC_HOME}/client/params/ClientPNames.o \
                        ${SRC_HOME}/client/params/HttpClientParams.o \
                        ${SRC_HOME}/message/ParserCursor.o \
                        ${SRC_HOME}/message/BasicHeader.o \
                        ${SRC_HOME}/message/BasicHeaderValueFormatter.o \
                        ${SRC_HOME}/message/BasicHeaderValueParser.o \
                        ${SRC_HOME}/message/BasicHeaderElement.o \
                        ${SRC_HOME}/message/BasicNameValuePair.o \
                        ${SRC_HOME}/message/BasicLineFormatter.o \
                        ${SRC_HOME}/message/BasicRequestLine.o \
                        ${SRC_HOME}/message/AbstractHttpMessage.o \
                        ${SRC_HOME}/message/BasicHttpRequest.o \
                        ${SRC_HOME}/message/HeaderGroup.o \
                        ${SRC_HOME}/message/BasicListHeaderIterator.o \
                        ${SRC_HOME}/message/BasicHeaderIterator.o \
                        ${SRC_HOME}/message/BasicHeaderElementIterator.o \
                        ${SRC_HOME}/message/BufferedHeader.o \
                        ${SRC_HOME}/message/BasicStatusLine.o \
                        ${SRC_HOME}/message/BasicLineParser.o \
                        ${SRC_HOME}/protocol/HttpContext.o \
                        ${SRC_HOME}/protocol/ExecutionContext.o \
                        ${SRC_HOME}/protocol/BasicHttpContext.o \
                        ${SRC_HOME}/protocol/DefaultedHttpContext.o \
                        ${SRC_HOME}/protocol/HttpDateGenerator.o \
                        ${SRC_HOME}/protocol/UriPatternMatcher.o \
                        ${SRC_HOME}/protocol/SyncBasicHttpContext.o $(LDFLAGS)

clean:
	$(RM) main ${SRC_HOME}/util/StringUtils.o ${SRC_HOME}/Main.o ${SRC_HOME}/protocol/HTTP.o ${SRC_HOME}/protocol/HttpHost.o ${SRC_HOME}/protocol/HttpVersion.o ${SRC_HOME}/net/URI.o ${SRC_HOME}/net/NameResolver.o ${SRC_HOME}/net/InetSocketAddress.o ${SRC_HOME}/net/URLStreamHandler.o ${SRC_HOME}/net/HttpHandler.o ${SRC_HOME}/net/HttpsHandler.o ${SRC_HOME}/net/FtpHandler.o ${SRC_HOME}/net/URL.o ${SRC_HOME}/protocol/ProtocolVersion.o ${SRC_HOME}/util/CharArrayBuffer.o ${SRC_HOME}/util/ByteArrayBuffer.o ${SRC_HOME}/params/CoreProtocolPNames.o ${SRC_HOME}/params/HttpProtocolParams.o ${SRC_HOME}/params/AbstractHttpParams.o ${SRC_HOME}/params/BasicHttpParams.o ${SRC_HOME}/params/Value.o ${SRC_HOME}/client/params/CookiePolicy.o ${SRC_HOME}/client/params/ClientPNames.o ${SRC_HOME}/client/params/HttpClientParams.o ${SRC_HOME}/message/ParserCursor.o ${SRC_HOME}/message/BasicHeader.o ${SRC_HOME}/message/BasicHeaderValueFormatter.o ${SRC_HOME}/message/BasicHeaderValueParser.o ${SRC_HOME}/message/BasicHeaderElement.o ${SRC_HOME}/message/BasicNameValuePair.o ${SRC_HOME}/message/BasicLineFormatter.o ${SRC_HOME}/message/BasicRequestLine.o ${SRC_HOME}/message/AbstractHttpMessage.o ${SRC_HOME}/message/BasicHttpRequest.o ${SRC_HOME}/message/HeaderGroup.o ${SRC_HOME}/message/BasicListHeaderIterator.o ${SRC_HOME}/message/BasicHeaderIterator.o ${SRC_HOME}/message/BasicHeaderElementIterator.o ${SRC_HOME}/message/BufferedHeader.o ${SRC_HOME}/message/BasicStatusLine.o ${SRC_HOME}/message/BasicLineParser.o ${SRC_HOME}/protocol/HttpContext.o ${SRC_HOME}/protocol/ExecutionContext.o ${SRC_HOME}/protocol/BasicHttpContext.o ${SRC_HOME}/protocol/DefaultedHttpContext.o ${SRC_HOME}/protocol/HttpDateGenerator.o ${SRC_HOME}/protocol/UriPatternMatcher.o ${SRC_HOME}/protocol/SyncBasicHttpContext.o 
