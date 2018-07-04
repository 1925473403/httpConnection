SRC_HOME=/home/fworks/replay/httpConnection/http
g++ -g -m64 -std="c++11" \
    -I${SRC_HOME}/protocol \
    -I${SRC_HOME}/conn/scheme \
    -I${SRC_HOME}/util \
    -I${SRC_HOME}/inc \
    -I${SRC_HOME}/net \
    -o ${SRC_HOME}/conn/scheme/test/main \
    ${SRC_HOME}/conn/scheme/test/Main.cc \
    ${SRC_HOME}/HttpHost.cc \
    ${SRC_HOME}/util/CharArrayBuffer.cc \
    ${SRC_HOME}/protocol/HTTP.cc \
    ${SRC_HOME}/net/InetSocketAddress.cc \
    ${SRC_HOME}/conn/scheme/NameResolver.cc -lnsl 
#${SRC_HOME}/conn/scheme/SchemeRegistry.cc \
#${SRC_HOME}/conn/scheme/Scheme.cc \
