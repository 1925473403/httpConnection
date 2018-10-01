CXX=g++
CP	=	cp
CXXFLAGS= -Wall -fPIC -g -m64 -std=c++11 $(INCLUDEDIRS)
LDFLAGS=-lpthread -shared -lnsl -lresolv -L${SRC_HOME}/util -lutil -L${SRC_HOME}/params -lparams
INCLUDEDIRS = -I${SRC_HOME}/inc -I${SRC_HOME}/protocol -I${SRC_HOME}/util -I${SRC_HOME}/params -I${SRC_HOME}/net 
SRC_HOME=/home/fworks/httpConnection/http
all:	libnet.so
libnet.so:	${SRC_HOME}/net/URI.o \
	${SRC_HOME}/net/NameResolver.o \
	${SRC_HOME}/net/InetSocketAddress.o \
	${SRC_HOME}/net/URLStreamHandler.o \
	${SRC_HOME}/net/HttpHandler.o \
	${SRC_HOME}/net/ByteArrayInputStream.o \
	${SRC_HOME}/net/HttpsHandler.o \
	${SRC_HOME}/net/FtpHandler.o \
	${SRC_HOME}/net/SocketInputStream.o \
	${SRC_HOME}/net/SocketOutputStream.o \
	${SRC_HOME}/net/AbstractPlainSocketImpl.o \
	${SRC_HOME}/net/DualStackPlainSocketImpl.o \
	${SRC_HOME}/net/ServerSocket.o \
	${SRC_HOME}/net/SocketImpl.o \
	${SRC_HOME}/net/URL.o \
	${SRC_HOME}/net/Socket.o 
	$(CXX) $(CXXFLAGS) -o libnet.so ${SRC_HOME}/net/URI.o \
	${SRC_HOME}/net/NameResolver.o \
	${SRC_HOME}/net/InetSocketAddress.o \
	${SRC_HOME}/net/URLStreamHandler.o \
	${SRC_HOME}/net/HttpHandler.o \
	${SRC_HOME}/net/ByteArrayInputStream.o \
	${SRC_HOME}/net/HttpsHandler.o \
	${SRC_HOME}/net/FtpHandler.o \
	${SRC_HOME}/net/SocketInputStream.o \
	${SRC_HOME}/net/SocketOutputStream.o \
	${SRC_HOME}/net/AbstractPlainSocketImpl.o \
	${SRC_HOME}/net/DualStackPlainSocketImpl.o \
	${SRC_HOME}/net/ServerSocket.o \
	${SRC_HOME}/net/SocketImpl.o \
	${SRC_HOME}/net/URL.o \
	${SRC_HOME}/net/Socket.o $(LDFLAGS)

clean:
	$(RM) libnet.so ${SRC_HOME}/net/URI.o \
	${SRC_HOME}/net/NameResolver.o \
	${SRC_HOME}/net/InetSocketAddress.o \
	${SRC_HOME}/net/URLStreamHandler.o \
	${SRC_HOME}/net/HttpHandler.o \
	${SRC_HOME}/net/HttpsHandler.o \
	${SRC_HOME}/net/FtpHandler.o \
	${SRC_HOME}/net/SocketInputStream.o \
	${SRC_HOME}/net/SocketOutputStream.o \
	${SRC_HOME}/net/AbstractPlainSocketImpl.o \
	${SRC_HOME}/net/ByteArrayInputStream.o \
	${SRC_HOME}/net/DualStackPlainSocketImpl.o \
	${SRC_HOME}/net/ServerSocket.o \
	${SRC_HOME}/net/SocketImpl.o \
	${SRC_HOME}/net/URL.o \
	${SRC_HOME}/net/Socket.o \
	${SRC_HOME}/libs/libnet.so
install:
	$(CP) libnet.so ${SRC_HOME}/libs
