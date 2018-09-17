CXX=g++
SRC_HOME=/home/fworks/httpConnection/http
CXXFLAGS= -Wall -g -m64 -std=c++11 $(INCLUDEDIRS)
LDFLAGS=-lpthread -lnsl -lresolv -L${SRC_HOME}/params -lparams
INCLUDEDIRS = -I${SRC_HOME}/inc -I${SRC_HOME}/protocol -I${SRC_HOME}/util -I${SRC_HOME}/params
all:	Main
Main:	${SRC_HOME}/params/tests/Main.o \
    ${SRC_HOME}/protocol/HttpVersion.o \
    ${SRC_HOME}/protocol/ProtocolVersion.o \
    ${SRC_HOME}/util/CharArrayBuffer.o \
    ${SRC_HOME}/protocol/HTTP.o
	$(CXX) $(CXXFLAGS) -o main  ${SRC_HOME}/params/tests/Main.o \
    ${SRC_HOME}/protocol/HttpVersion.o \
    ${SRC_HOME}/protocol/ProtocolVersion.o \
    ${SRC_HOME}/util/CharArrayBuffer.o \
    ${SRC_HOME}/protocol/HTTP.o $(LDFLAGS)
clean:
	$(RM) main  ${SRC_HOME}/params/tests/Main.o \
    ${SRC_HOME}/protocol/HttpVersion.o \
    ${SRC_HOME}/protocol/ProtocolVersion.o \
    ${SRC_HOME}/util/CharArrayBuffer.o \
    ${SRC_HOME}/protocol/HTTP.o

