CXX=g++
CXXFLAGS=-Wall -g -m64 -std=c++11 $(INCLUDEDIRS)
LDFLAGS=-lpthread -lnsl -lresolv -L${SRC_HOME}/util lutil -L${SRC_HOME}/params -lparams -L${SRC_HOME}/net -lnet
INCLUDEDIRS = -I${SRC_HOME}/inc -I${SRC_HOME}/protocol -I${SRC_HOME}/util -I${SRC_HOME}/params -I${SRC_HOME}/net -I${SRC_HOME}/message -I${SRC_HOME}/client/params 
SRC_HOME=/home/fworks/httpConnection/http
all:	libmessage.so
libmessage.so:	${SRC_HOME}/message/BasicHeaderValueParser.o \
	${SRC_HOME}/message/BasicHeaderValueFormatter.o \
	${SRC_HOME}/message/BasicHeaderIterator.o \
	${SRC_HOME}/message/BasicHeaderElementIterator.o \
	${SRC_HOME}/message/BasicHeaderElement.o \
	${SRC_HOME}/message/BasicHeader.o \
	${SRC_HOME}/message/AbstractHttpMessage.o \
	${SRC_HOME}/message/ParserCursor.o \
	${SRC_HOME}/message/HeaderGroup.o \
	${SRC_HOME}/message/BufferedHeader.o \
	${SRC_HOME}/message/BasicStatusLine.o \
	${SRC_HOME}/message/BasicRequestLine.o \
	${SRC_HOME}/message/BasicNameValuePair.o \
	${SRC_HOME}/message/BasicListHeaderIterator.o \
	${SRC_HOME}/message/BasicLineParser.o \
	${SRC_HOME}/message/BasicLineFormatter.o \
	${SRC_HOME}/message/BasicHttpResponse.o \
	${SRC_HOME}/message/BasicHttpRequest.o \
	${SRC_HOME}/message/BasicHttpEntityEnclosingRequest.o
	$(CXX) $(CXXFLAGS) -o libmessage.so ${SRC_HOME}/message/BasicHeaderValueParser.o \
	${SRC_HOME}/message/BasicHeaderValueFormatter.o \
	${SRC_HOME}/message/BasicHeaderIterator.o \
	${SRC_HOME}/message/BasicHeaderElementIterator.o \
	${SRC_HOME}/message/BasicHeaderElement.o \
	${SRC_HOME}/message/BasicHeader.o \
	${SRC_HOME}/message/AbstractHttpMessage.o \
	${SRC_HOME}/message/ParserCursor.o \
	${SRC_HOME}/message/HeaderGroup.o \
	${SRC_HOME}/message/BufferedHeader.o \
	${SRC_HOME}/message/BasicStatusLine.o \
	${SRC_HOME}/message/BasicRequestLine.o \
	${SRC_HOME}/message/BasicNameValuePair.o \
	${SRC_HOME}/message/BasicListHeaderIterator.o \
	${SRC_HOME}/message/BasicLineParser.o \
	${SRC_HOME}/message/BasicLineFormatter.o \
	${SRC_HOME}/message/BasicHttpResponse.o \
	${SRC_HOME}/message/BasicHttpEntityEnclosingRequest.o $(LDFLAGS)
clean:
	$(RM) libmessage.so ${SRC_HOME}/message/BasicHeaderValueParser.o \
	${SRC_HOME}/message/BasicHeaderValueFormatter.o \
	${SRC_HOME}/message/BasicHeaderIterator.o \
	${SRC_HOME}/message/BasicHeaderElementIterator.o \
	${SRC_HOME}/message/BasicHeaderElement.o \
	${SRC_HOME}/message/BasicHeader.o \
	${SRC_HOME}/message/AbstractHttpMessage.o \
	${SRC_HOME}/message/ParserCursor.o \
	${SRC_HOME}/message/HeaderGroup.o \
	${SRC_HOME}/message/BufferedHeader.o \
	${SRC_HOME}/message/BasicStatusLine.o \
	${SRC_HOME}/message/BasicRequestLine.o \
	${SRC_HOME}/message/BasicNameValuePair.o \
	${SRC_HOME}/message/BasicListHeaderIterator.o \
	${SRC_HOME}/message/BasicLineParser.o \
	${SRC_HOME}/message/BasicLineFormatter.o \
	${SRC_HOME}/message/BasicHttpResponse.o \
	${SRC_HOME}/message/BasicHttpEntityEnclosingRequest.o 
