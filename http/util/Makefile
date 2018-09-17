CXX=g++
CP = cp
SRC_HOME=/home/fworks/httpConnection/http
CXXFLAGS= -Wall -fPIC -g -m64 -std=c++11 $(INCLUDEDIRS)
LDFLAGS=-shared -lpthread -lnsl -lresolv 
INCLUDEDIRS = -I${SRC_HOME}/inc -I${SRC_HOME}/protocol -I${SRC_HOME}/util -I${SRC_HOME}/params
all:	libutil.so
libutil.so:	${SRC_HOME}/util/ByteArrayBuffer.o \
	${SRC_HOME}/util/StringUtils.o \
    ${SRC_HOME}/util/CharArrayBuffer.o
	$(CXX) $(CXXFLAGS) -o libutil.so  ${SRC_HOME}/util/ByteArrayBuffer.o \
	${SRC_HOME}/util/StringUtils.o \
    ${SRC_HOME}/util/CharArrayBuffer.o  $(LDFLAGS)
clean:
	$(RM) libutil.so  ${SRC_HOME}/util/ByteArrayBuffer.o \
	${SRC_HOME}/util/StringUtils.o \
    ${SRC_HOME}/util/CharArrayBuffer.o ${SRC_HOME}/libs/libutil.so
install:
	$(CP) libutil.so ${SRC_HOME}/libs/
