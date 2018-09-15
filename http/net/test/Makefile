CXX=g++
CXXFLAGS= -Wall -g -m64 -std=c++11 $(INCLUDEDIRS)
LDFLAGS=-lpthread -lnsl -lresolv
INCLUDEDIRS = -I${SRC_HOME}/inc -I${SRC_HOME}/protocol -I${SRC_HOME}/util -I${SRC_HOME}/params -I${SRC_HOME}/net 
SRC_HOME=/home/fworks/httpConnection/http
all:	Main ClientMain
Main:	${SRC_HOME}/net/test/Main.o ${SRC_HOME}/util/StringUtils.o  ${SRC_HOME}/protocol/HTTP.o ${SRC_HOME}/HttpHost.o ${SRC_HOME}/net/URI.o ${SRC_HOME}/net/NameResolver.o ${SRC_HOME}/net/InetSocketAddress.o ${SRC_HOME}/net/URLStreamHandler.o ${SRC_HOME}/net/HttpHandler.o ${SRC_HOME}/net/HttpsHandler.o ${SRC_HOME}/net/FtpHandler.o ${SRC_HOME}/net/SocketInputStream.o ${SRC_HOME}/net/SocketOutputStream.o ${SRC_HOME}/net/AbstractPlainSocketImpl.o ${SRC_HOME}/net/DualStackPlainSocketImpl.o ${SRC_HOME}/net/ServerSocket.o ${SRC_HOME}/net/SocketImpl.o ${SRC_HOME}/net/URL.o ${SRC_HOME}/util/CharArrayBuffer.o ${SRC_HOME}/util/ByteArrayBuffer.o ${SRC_HOME}/params/Value.o ${SRC_HOME}/net/Socket.o 
	$(CXX) $(CXXFLAGS) -o main ${SRC_HOME}/net/test/Main.o ${SRC_HOME}/protocol/HTTP.o ${SRC_HOME}/util/StringUtils.o    ${SRC_HOME}/net/URI.o ${SRC_HOME}/net/NameResolver.o ${SRC_HOME}/net/InetSocketAddress.o ${SRC_HOME}/net/URLStreamHandler.o ${SRC_HOME}/net/HttpHandler.o ${SRC_HOME}/net/HttpsHandler.o ${SRC_HOME}/net/FtpHandler.o ${SRC_HOME}/net/SocketInputStream.o ${SRC_HOME}/net/SocketOutputStream.o ${SRC_HOME}/net/AbstractPlainSocketImpl.o ${SRC_HOME}/net/DualStackPlainSocketImpl.o ${SRC_HOME}/net/ServerSocket.o ${SRC_HOME}/net/SocketImpl.o ${SRC_HOME}/net/Socket.o ${SRC_HOME}/net/URL.o ${SRC_HOME}/util/CharArrayBuffer.o ${SRC_HOME}/util/ByteArrayBuffer.o ${SRC_HOME}/params/Value.o $(LDFLAGS)
ClientMain:	${SRC_HOME}/net/test/ClientMain.o ${SRC_HOME}/util/StringUtils.o  ${SRC_HOME}/protocol/HTTP.o ${SRC_HOME}/HttpHost.o ${SRC_HOME}/net/URI.o ${SRC_HOME}/net/NameResolver.o ${SRC_HOME}/net/InetSocketAddress.o ${SRC_HOME}/net/URLStreamHandler.o ${SRC_HOME}/net/HttpHandler.o ${SRC_HOME}/net/HttpsHandler.o ${SRC_HOME}/net/FtpHandler.o ${SRC_HOME}/net/SocketInputStream.o ${SRC_HOME}/net/SocketOutputStream.o ${SRC_HOME}/net/AbstractPlainSocketImpl.o ${SRC_HOME}/net/DualStackPlainSocketImpl.o ${SRC_HOME}/net/ServerSocket.o ${SRC_HOME}/net/SocketImpl.o ${SRC_HOME}/net/URL.o ${SRC_HOME}/util/CharArrayBuffer.o ${SRC_HOME}/util/ByteArrayBuffer.o ${SRC_HOME}/params/Value.o ${SRC_HOME}/net/Socket.o 
	$(CXX) $(CXXFLAGS) -o ClientMain ${SRC_HOME}/net/test/ClientMain.o ${SRC_HOME}/protocol/HTTP.o ${SRC_HOME}/util/StringUtils.o    ${SRC_HOME}/net/URI.o ${SRC_HOME}/net/NameResolver.o ${SRC_HOME}/net/InetSocketAddress.o ${SRC_HOME}/net/URLStreamHandler.o ${SRC_HOME}/net/HttpHandler.o ${SRC_HOME}/net/HttpsHandler.o ${SRC_HOME}/net/FtpHandler.o ${SRC_HOME}/net/SocketInputStream.o ${SRC_HOME}/net/SocketOutputStream.o ${SRC_HOME}/net/AbstractPlainSocketImpl.o ${SRC_HOME}/net/DualStackPlainSocketImpl.o ${SRC_HOME}/net/ServerSocket.o ${SRC_HOME}/net/SocketImpl.o ${SRC_HOME}/net/Socket.o ${SRC_HOME}/net/URL.o ${SRC_HOME}/util/CharArrayBuffer.o ${SRC_HOME}/util/ByteArrayBuffer.o ${SRC_HOME}/params/Value.o $(LDFLAGS)

Main.o:	${SRC_HOME}/net/test/Main.cc
ClientMain.o:	${SRC_HOME}/net/test/ClientMain.cc
StringUtils.o:	${SRC_HOME}/util/StringUtils.cc
URI.o: ${SRC_HOME}/net/URI.cc 
NameResolver.o:	${SRC_HOME}/net/NameResolver.cc 
HTTP.o: ${SRC_HOME}/protocol/HTTP.cc
InetSocketAddress..o:	${SRC_HOME}/net/InetSocketAddress.cc 
URLStreamHandler.o:	${SRC_HOME}/net/URLStreamHandler.cc 
HttpHandler.o: ${SRC_HOME}/net/HttpHandler.cc 
HttpsHandler.o:	${SRC_HOME}/net/HttpsHandler.cc 
FtpHandler.o: ${SRC_HOME}/net/FtpHandler.cc 
SocketInputStream.o: ${SRC_HOME}/net/SocketInputStream.cc 
SocketOutputStream.o: ${SRC_HOME}/net/SocketOutputStream.cc 
AbstractPlainSocketImpl.o: ${SRC_HOME}/net/AbstractPlainSocketImpl.cc 
DualStackPlainSocketImpl.o:	${SRC_HOME}/net/DualStackPlainSocketImpl.cc 
ServerSocket.o:	${SRC_HOME}/net/ServerSocket.cc 
SocketImpl.o: ${SRC_HOME}/net/SocketImpl.cc 
URL.o: ${SRC_HOME}/net/URL.cc 
CharArrayBuffer.o: ${SRC_HOME}/util/CharArrayBuffer.cc 
ByteArrayBuffer.o: ${SRC_HOME}/util/ByteArrayBuffer.cc 
Value.o: ${SRC_HOME}/params/Value.cc 
Socket.o: ${SRC_HOME}/net/Socket.cc 
clean:
	$(RM) main ClientMain ${SRC_HOME}/net/test/ClientMain.o ${SRC_HOME}/net/test/Main.o ${SRC_HOME}/HttpHost.o ${SRC_HOME}/util/StringUtils.o ${SRC_HOME}/protocol/HTTP.o  ${SRC_HOME}/net/URI.o ${SRC_HOME}/net/NameResolver.o ${SRC_HOME}/net/InetSocketAddress.o ${SRC_HOME}/net/URLStreamHandler.o ${SRC_HOME}/net/HttpHandler.o ${SRC_HOME}/net/HttpsHandler.o ${SRC_HOME}/net/FtpHandler.o ${SRC_HOME}/net/SocketInputStream.o ${SRC_HOME}/net/SocketOutputStream.o ${SRC_HOME}/net/AbstractPlainSocketImpl.o ${SRC_HOME}/net/DualStackPlainSocketImpl.o ${SRC_HOME}/net/ServerSocket.o ${SRC_HOME}/net/SocketImpl.o ${SRC_HOME}/net/Socket.o ${SRC_HOME}/net/URL.o ${SRC_HOME}/util/CharArrayBuffer.o ${SRC_HOME}/util/ByteArrayBuffer.o ${SRC_HOME}/params/Value.o 
