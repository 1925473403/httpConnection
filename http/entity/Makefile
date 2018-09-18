CXX=g++
CP = cp
SRC_HOME=/home/fworks/httpConnection/http
CXXFLAGS= -Wall -fPIC -g -m64 -std=c++11 $(INCLUDEDIRS)
LDFLAGS=-shared -lpthread -lnsl -lresolv -L${SRC_HOME}/util -lutil -L${SRC_HOME}/params -lparams -L${SRC_HOME}/net -lnet
INCLUDEDIRS = -I${SRC_HOME}/inc -I${SRC_HOME}/protocol -I${SRC_HOME}/util -I${SRC_HOME}/params -I${SRC_HOME}/net -I${SRC_HOME}/message
all:	libentity.so
libentity.so:	${SRC_HOME}/entity/ContentLengthStrategy.o \
	${SRC_HOME}/entity/HttpEntityWrapper.o \
	${SRC_HOME}/entity/AbstractHttpEntity.o \
	${SRC_HOME}/entity/BasicHttpEntity.o \
	${SRC_HOME}/entity/EntityTemplate.o \
	${SRC_HOME}/entity/StringEntity.o \
	${SRC_HOME}/entity/BufferedHttpEntity.o \
	${SRC_HOME}/entity/ByteArrayEntity.o \
	${SRC_HOME}/entity/InputStreamEntity.o
	$(CXX) $(CXXFLAGS) -o libentity.so ${SRC_HOME}/entity/ContentLengthStrategy.o \
	${SRC_HOME}/entity/HttpEntityWrapper.o \
	${SRC_HOME}/entity/AbstractHttpEntity.o \
	${SRC_HOME}/entity/BasicHttpEntity.o \
	${SRC_HOME}/entity/EntityTemplate.o \
	${SRC_HOME}/entity/StringEntity.o \
	${SRC_HOME}/entity/BufferedHttpEntity.o \
	${SRC_HOME}/entity/ByteArrayEntity.o \
	${SRC_HOME}/entity/InputStreamEntity.o $(LDFLAGS)
clean:
	$(RM) libentity.so ${SRC_HOME}/entity/ContentLengthStrategy.o \
	${SRC_HOME}/entity/HttpEntityWrapper.o \
	${SRC_HOME}/entity/AbstractHttpEntity.o \
	${SRC_HOME}/entity/BasicHttpEntity.o \
	${SRC_HOME}/entity/EntityTemplate.o \
	${SRC_HOME}/entity/StringEntity.o \
	${SRC_HOME}/entity/BufferedHttpEntity.o \
	${SRC_HOME}/entity/ByteArrayEntity.o \
	${SRC_HOME}/entity/InputStreamEntity.o \
	${SRC_HOME}/libs/libentity.so
install:
	$(CP) libentity.so ${SRC_HOME}/entity/ContentLengthStrategy.o \
	${SRC_HOME}/entity/HttpEntityWrapper.o \
	${SRC_HOME}/entity/AbstractHttpEntity.o \
	${SRC_HOME}/entity/BasicHttpEntity.o \
	${SRC_HOME}/entity/EntityTemplate.o \
	${SRC_HOME}/entity/StringEntity.o \
	${SRC_HOME}/entity/BufferedHttpEntity.o \
	${SRC_HOME}/entity/ByteArrayEntity.o \
	${SRC_HOME}/entity/InputStreamEntity.o 
