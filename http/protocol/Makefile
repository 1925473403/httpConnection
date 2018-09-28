CXX=g++
CP = cp
SRC_HOME=/home/fworks/httpConnection/http
CXXFLAGS= -Wall -fPIC -g -m64 -std=c++11 $(INCLUDEDIRS)
LDFLAGS=-shared -lpthread -lnsl -lresolv -L${SRC_HOME}/util -lutil -L${SRC_HOME}/params -lparams
INCLUDEDIRS = -I${SRC_HOME}/inc -I${SRC_HOME}/protocol -I${SRC_HOME}/util -I${SRC_HOME}/params -I${SRC_HOME}/net -I${SRC_HOME}/entity -I${SRC_HOME}/entity/params
all:	libprotocol.so
libprotocol.so:	${SRC_HOME}/protocol/HttpHost.o \
	${SRC_HOME}/protocol/HttpDateGenerator.o \
	${SRC_HOME}/protocol/HttpContext.o \
	${SRC_HOME}/protocol/HTTP.o \
	${SRC_HOME}/protocol/ExecutionContext.o \
	${SRC_HOME}/protocol/HttpVersion.o \
	${SRC_HOME}/protocol/ProtocolVersion.o \
	${SRC_HOME}/protocol/SyncBasicHttpContext.o \
	${SRC_HOME}/protocol/UriPatternMatcher.o \
	${SRC_HOME}/protocol/DefaultedHttpContext.o \
	${SRC_HOME}/protocol/BasicHttpContext.o \
	${SRC_HOME}/protocol/RequestExpectContinue.o \
	${SRC_HOME}/protocol/RequestContent.o \
	${SRC_HOME}/protocol/ResponseContent.o \
	${SRC_HOME}/protocol/HttpRequestHandlerRegistry.o \
	${SRC_HOME}/protocol/ResponseConnControl.o \
	${SRC_HOME}/protocol/ResponseDate.o \
	${SRC_HOME}/protocol/ResponseServer.o \
	${SRC_HOME}/protocol/HttpService.o \
	${SRC_HOME}/protocol/HttpRequestExecutor.o
	$(CXX) $(CXXFLAGS) -o libprotocol.so  ${SRC_HOME}/protocol/HttpHost.o \
	${SRC_HOME}/protocol/HttpDateGenerator.o \
	${SRC_HOME}/protocol/HttpContext.o \
	${SRC_HOME}/protocol/HTTP.o \
	${SRC_HOME}/protocol/HttpVersion.o \
	${SRC_HOME}/protocol/ProtocolVersion.o \
	${SRC_HOME}/protocol/UriPatternMatcher.o \
	${SRC_HOME}/protocol/SyncBasicHttpContext.o \
	${SRC_HOME}/protocol/ExecutionContext.o \
	${SRC_HOME}/protocol/ResponseContent.o \
	${SRC_HOME}/protocol/RequestContent.o \
	${SRC_HOME}/protocol/RequestExpectContinue.o \
	${SRC_HOME}/protocol/DefaultedHttpContext.o \
	${SRC_HOME}/protocol/BasicHttpContext.o \
	${SRC_HOME}/protocol/HttpService.o \
	${SRC_HOME}/protocol/ResponseDate.o \
	${SRC_HOME}/protocol/ResponseConnControl.o \
	${SRC_HOME}/protocol/HttpRequestHandlerRegistry.o \
	${SRC_HOME}/protocol/HttpRequestExecutor.o \
	${SRC_HOME}/protocol/ResponseServer.o $(LDFLAGS)
clean:
	$(RM) libprotocol.so  ${SRC_HOME}/protocol/HttpHost.o \
	${SRC_HOME}/protocol/HttpDateGenerator.o \
	${SRC_HOME}/protocol/HttpContext.o \
	${SRC_HOME}/protocol/HTTP.o \
	${SRC_HOME}/protocol/ExecutionContext.o \
	${SRC_HOME}/protocol/DefaultedHttpContext.o \
	${SRC_HOME}/protocol/BasicHttpContext.o \
	${SRC_HOME}/protocol/ResponseContent.o \
	${SRC_HOME}/protocol/RequestContent.o \
	${SRC_HOME}/protocol/RequestExpectContinue.o \
	${SRC_HOME}/protocol/HttpVersion.o \
	${SRC_HOME}/protocol/ProtocolVersion.o \
	${SRC_HOME}/protocol/UriPatternMatcher.o \
	${SRC_HOME}/protocol/SyncBasicHttpContext.o \
	${SRC_HOME}/protocol/ResponseDate.o \
	${SRC_HOME}/protocol/ResponseConnControl.o \
	${SRC_HOME}/protocol/HttpService.o \
	${SRC_HOME}/protocol/HttpRequestHandlerRegistry.o \
	${SRC_HOME}/protocol/HttpRequestExecutor.o \
	${SRC_HOME}/protocol/ResponseServer.o \
	${SRC_HOME}/libs/libprotocol.so
install:
	$(CP) libprotocol.so ${SRC_HOME}/libs/
