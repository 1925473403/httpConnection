CXX=g++
CP = cp
SRC_HOME=/home/fworks/httpConnection/http
CXXFLAGS= -Wall -fPIC -g -m64 -std=c++11 $(INCLUDEDIRS)
LDFLAGS=-shared -lpthread -lnsl -lresolv
INCLUDEDIRS = -I${SRC_HOME}/inc -I${SRC_HOME}/protocol -I${SRC_HOME}/util -I${SRC_HOME}/params
all:	libparams.so
libparams.so:	${SRC_HOME}/params/AbstractHttpParams.o \
	${SRC_HOME}/params/BasicHttpParams.o \
    ${SRC_HOME}/params/Value.o \
    ${SRC_HOME}/params/CoreProtocolPNames.o \
    ${SRC_HOME}/params/HttpProtocolParams.o \
    ${SRC_HOME}/params/DefaultedHttpParams.o \
    ${SRC_HOME}/params/CoreConnectionPNames.o \
    ${SRC_HOME}/params/HttpConnectionParams.o \
    ${SRC_HOME}/params/HttpAbstractParamBean.o \
    ${SRC_HOME}/params/HttpConnectionParamBean.o
	$(CXX) $(CXXFLAGS) -o libparams.so  ${SRC_HOME}/params/AbstractHttpParams.o \
	${SRC_HOME}/params/BasicHttpParams.o \
    ${SRC_HOME}/params/Value.o \
    ${SRC_HOME}/params/CoreProtocolPNames.o \
    ${SRC_HOME}/params/HttpProtocolParams.o \
    ${SRC_HOME}/params/DefaultedHttpParams.o \
    ${SRC_HOME}/params/CoreConnectionPNames.o \
    ${SRC_HOME}/params/HttpConnectionParams.o \
    ${SRC_HOME}/params/HttpAbstractParamBean.o \
    ${SRC_HOME}/params/HttpConnectionParamBean.o  $(LDFLAGS)
clean:
	$(RM) libparams.so  ${SRC_HOME}/params/AbstractHttpParams.o \
	${SRC_HOME}/params/BasicHttpParams.o \
    ${SRC_HOME}/params/Value.o \
    ${SRC_HOME}/params/CoreProtocolPNames.o \
    ${SRC_HOME}/params/HttpProtocolParams.o \
    ${SRC_HOME}/params/DefaultedHttpParams.o \
    ${SRC_HOME}/params/CoreConnectionPNames.o \
    ${SRC_HOME}/params/HttpConnectionParams.o \
    ${SRC_HOME}/params/HttpAbstractParamBean.o \
    ${SRC_HOME}/params/HttpConnectionParamBean.o
install:
	$(CP) libparams.so ${SRC_HOME}/libs/
