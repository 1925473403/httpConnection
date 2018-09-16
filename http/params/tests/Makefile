CXX=g++
SRC_HOME=/home/fworks/httpConnection/http
CXXFLAGS= -Wall -g -m64 -std=c++11 $(INCLUDEDIRS)
LDFLAGS=-lpthread -lnsl -lresolv
INCLUDEDIRS = -I${SRC_HOME}/inc -I${SRC_HOME}/protocol -I${SRC_HOME}/util -I${SRC_HOME}/params
all:	Main
Main:	${SRC_HOME}/params/tests/Main.o \
	${SRC_HOME}/params/AbstractHttpParams.o \
	${SRC_HOME}/params/BasicHttpParams.o \
    ${SRC_HOME}/params/Value.o \
    ${SRC_HOME}/HttpVersion.o \
    ${SRC_HOME}/ProtocolVersion.o \
    ${SRC_HOME}/params/CoreProtocolPNames.o \
    ${SRC_HOME}/params/HttpProtocolParams.o \
    ${SRC_HOME}/params/DefaultedHttpParams.o \
    ${SRC_HOME}/params/CoreConnectionPNames.o \
    ${SRC_HOME}/params/HttpConnectionParams.o \
    ${SRC_HOME}/params/HttpAbstractParamBean.o \
    ${SRC_HOME}/params/HttpConnectionParamBean.o \
    ${SRC_HOME}/util/CharArrayBuffer.o \
    ${SRC_HOME}/protocol/HTTP.o
	$(CXX) $(CXXFLAGS) -o main  ${SRC_HOME}/params/tests/Main.o \
	${SRC_HOME}/params/AbstractHttpParams.o \
	${SRC_HOME}/params/BasicHttpParams.o \
    ${SRC_HOME}/params/Value.o \
    ${SRC_HOME}/HttpVersion.o \
    ${SRC_HOME}/ProtocolVersion.o \
    ${SRC_HOME}/params/CoreProtocolPNames.o \
    ${SRC_HOME}/params/HttpProtocolParams.o \
    ${SRC_HOME}/params/DefaultedHttpParams.o \
    ${SRC_HOME}/params/CoreConnectionPNames.o \
    ${SRC_HOME}/params/HttpConnectionParams.o \
    ${SRC_HOME}/params/HttpAbstractParamBean.o \
    ${SRC_HOME}/params/HttpConnectionParamBean.o \
    ${SRC_HOME}/util/CharArrayBuffer.o \
    ${SRC_HOME}/protocol/HTTP.o $(LDFLAGS)
clean:
	$(RM) main  ${SRC_HOME}/params/tests/Main.o \
	${SRC_HOME}/params/AbstractHttpParams.o \
	${SRC_HOME}/params/BasicHttpParams.o \
    ${SRC_HOME}/params/Value.o \
    ${SRC_HOME}/HttpVersion.o \
    ${SRC_HOME}/ProtocolVersion.o \
    ${SRC_HOME}/params/CoreProtocolPNames.o \
    ${SRC_HOME}/params/HttpProtocolParams.o \
    ${SRC_HOME}/params/DefaultedHttpParams.o \
    ${SRC_HOME}/params/CoreConnectionPNames.o \
    ${SRC_HOME}/params/HttpConnectionParams.o \
    ${SRC_HOME}/params/HttpAbstractParamBean.o \
    ${SRC_HOME}/params/HttpConnectionParamBean.o \
    ${SRC_HOME}/util/CharArrayBuffer.o \
    ${SRC_HOME}/protocol/HTTP.o

