CXX=g++
CXXFLAGS=-Wall -g -m64 -std=c++11 $(INCLUDEDIRS)
LDFLAGS=-lpthread -lnsl -lresolv
INCLUDEDIRS = -I${SRC_HOME}/inc -I${SRC_HOME}/protocol -I${SRC_HOME}/util -I${SRC_HOME}/params -I${SRC_HOME}/net 
SRC_HOME=/home/fworks/httpConnection/http
all:	Main
Main:	${SRC_HOME}/net/test/Main.o ${SRC_HOME}/util/StringUtils.o  ${SRC_HOME}/protocol/HTTP.o ${SRC_HOME}/HttpHost.o ${SRC_HOME}/HttpVersion.o ${SRC_HOME}/net/URI.o ${SRC_HOME}/net/NameResolver.o ${SRC_HOME}/net/InetSocketAddress.o ${SRC_HOME}/net/URLStreamHandler.o ${SRC_HOME}/net/HttpHandler.o ${SRC_HOME}/net/HttpsHandler.o ${SRC_HOME}/net/FtpHandler.o ${SRC_HOME}/net/SocketInputStream.o ${SRC_HOME}/net/SocketOutputStream.o ${SRC_HOME}/net/AbstractPlainSocketImpl.o ${SRC_HOME}/net/DualStackPlainSocketImpl.o ${SRC_HOME}/net/ServerSocket.o ${SRC_HOME}/net/SocketImpl.o ${SRC_HOME}/net/Socket.o ${SRC_HOME}/net/URL.o ${SRC_HOME}/util/CharArrayBuffer.o ${SRC_HOME}/util/ByteArrayBuffer.o ${SRC_HOME}/params/Value.o
	$(CXX) $(CXXFLAGS) -o main ${SRC_HOME}/net/test/Main.o ${SRC_HOME}/util/StringUtils.o  ${SRC_HOME}/protocol/HTTP.o ${SRC_HOME}/HttpHost.o ${SRC_HOME}/HttpVersion.o ${SRC_HOME}/net/URI.o ${SRC_HOME}/net/NameResolver.o ${SRC_HOME}/net/InetSocketAddress.o ${SRC_HOME}/net/URLStreamHandler.o ${SRC_HOME}/net/HttpHandler.o ${SRC_HOME}/net/HttpsHandler.o ${SRC_HOME}/net/FtpHandler.o ${SRC_HOME}/net/SocketInputStream.o ${SRC_HOME}/net/SocketOutputStream.o ${SRC_HOME}/net/AbstractPlainSocketImpl.o ${SRC_HOME}/net/DualStackPlainSocketImpl.o ${SRC_HOME}/net/ServerSocket.o ${SRC_HOME}/net/SocketImpl.o ${SRC_HOME}/net/Socket.o ${SRC_HOME}/net/URL.o ${SRC_HOME}/util/CharArrayBuffer.o ${SRC_HOME}/util/ByteArrayBuffer.o ${SRC_HOME}/params/Value.o $(LDFLAGS)

Main.o:	${SRC_HOME}/net/test/Main.cc
StringUtils.o:	${SRC_HOME}/util/StringUtils.cc
#${SRC_HOME}/net/test/HTTP.o:	${SRC_HOME}/protocol/HTTP.cc 
#${SRC_HOME}/net/test/HttpHost.o:	${SRC_HOME}/HttpHost.cc 
#${SRC_HOME}/net/test/HttpVersion.o: ${SRC_HOME}/HttpVersion.cc 
#${SRC_HOME}/net/test/URI.o: ${SRC_HOME}/net/URI.cc 
#${SRC_HOME}/net/test/NameResolver.o:	${SRC_HOME}/net/NameResolver.cc 
#${SRC_HOME}/net/test/InetSocketAddress..o:	${SRC_HOME}/net/InetSocketAddress.cc 
#${SRC_HOME}/net/test/URLStreamHandler.o:	${SRC_HOME}/net/URLStreamHandler.cc 
#${SRC_HOME}/net/test/HttpHandler.o: ${SRC_HOME}/net/HttpHandler.cc 
#${SRC_HOME}/net/test/HttpsHandler.o:	${SRC_HOME}/net/HttpsHandler.cc 
#${SRC_HOME}/net/test/FtpHandler.o: ${SRC_HOME}/net/FtpHandler.cc 
#${SRC_HOME}/net/test/SocketInputStream.o: ${SRC_HOME}/net/SocketInputStream.cc 
#${SRC_HOME}/net/test/SocketOutputStream.o: ${SRC_HOME}/net/SocketOutputStream.cc 
#${SRC_HOME}/net/test/AbstractPlainSocketImpl.o: ${SRC_HOME}/net/AbstractPlainSocketImpl.cc 
#${SRC_HOME}/net/test/DualStackPlainSocketImpl.o:	${SRC_HOME}/net/DualStackPlainSocketImpl.cc 
#${SRC_HOME}/net/test/ServerSocket.o:	${SRC_HOME}/net/ServerSocket.cc 
#${SRC_HOME}/net/test/SocketImpl.o: ${SRC_HOME}/net/SocketImpl.cc 
#${SRC_HOME}/net/test/Socket.o: ${SRC_HOME}/net/Socket.cc 
#${SRC_HOME}/net/test/URL.o: ${SRC_HOME}/net/URL.cc 
#${SRC_HOME}/net/test/CharArrayBuffer.o: ${SRC_HOME}/util/CharArrayBuffer.cc 
#${SRC_HOME}/net/test/ByteArrayBuffer.o: ${SRC_HOME}/util/ByteArrayBuffer.cc 
#${SRC_HOME}/net/test/Value.o: ${SRC_HOME}/params/Value.cc 
clean:
	$(RM) main ${SRC_HOME}/net/test/Main.o ${SRC_HOME}/util/StringUtils.o  ${SRC_HOME}/protocol/HTTP.o ${SRC_HOME}/HttpHost.o ${SRC_HOME}/HttpVersion.o ${SRC_HOME}/net/URI.o ${SRC_HOME}/net/NameResolver.o ${SRC_HOME}/net/InetSocketAddress.o ${SRC_HOME}/net/URLStreamHandler.o ${SRC_HOME}/net/HttpHandler.o ${SRC_HOME}/net/HttpsHandler.o ${SRC_HOME}/net/FtpHandler.o ${SRC_HOME}/net/SocketInputStream.o ${SRC_HOME}/net/SocketOutputStream.o ${SRC_HOME}/net/AbstractPlainSocketImpl.o ${SRC_HOME}/net/DualStackPlainSocketImpl.o ${SRC_HOME}/net/ServerSocket.o ${SRC_HOME}/net/SocketImpl.o ${SRC_HOME}/net/Socket.o ${SRC_HOME}/net/URL.o ${SRC_HOME}/util/CharArrayBuffer.o ${SRC_HOME}/util/ByteArrayBuffer.o ${SRC_HOME}/params/Value.o 
