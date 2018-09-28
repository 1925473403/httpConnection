CXX=g++
CP = cp
SRC_HOME=/home/fworks/httpConnection/http
CXXFLAGS= -Wall -fPIC -g -m64 -std=c++11 $(INCLUDEDIRS)
LDFLAGS=-shared -lpthread -lnsl -lresolv
INCLUDEDIRS = -I${SRC_HOME}/inc -I${SRC_HOME}/protocol -I${SRC_HOME}/util -I${SRC_HOME}/params -I. -I${SRC_HOME}/cookie/params 
all:	libparams.so
libparams.so:	${SRC_HOME}/cookie/ClientCookie.o \
	${SRC_HOME}/cookie/CookieAttributeHandler.o \
	${SRC_HOME}/cookie/Cookie.o \
	${SRC_HOME}/cookie/CookieIdentityComparator.o \
	${SRC_HOME}/cookie/CookieOrigin.o \
	${SRC_HOME}/cookie/CookiePathComparator.o \
	${SRC_HOME}/cookie/CookieSpecFactory.o \
	${SRC_HOME}/cookie/CookieSpecRegistry.o \
	${SRC_HOME}/cookie/SetCookie.o \
	${SRC_HOME}/cookie/SetCookie2.o \
    ${SRC_HOME}/cookie/SM.o \
	${SRC_HOME}/cookie/params/CookieSpecPNames.o \
	${SRC_HOME}/cookie/params/CookieSpecParamBean.o
	$(CXX) $(CXXFLAGS) -o libcookie.so  ${SRC_HOME}/cookie/ClientCookie.o \
	${SRC_HOME}/cookie/CookieAttributeHandler.o \
	${SRC_HOME}/cookie/Cookie.o \
	${SRC_HOME}/cookie/CookieIdentityComparator.o \
	${SRC_HOME}/cookie/CookieOrigin.o \
	${SRC_HOME}/cookie/CookiePathComparator.o \
	${SRC_HOME}/cookie/CookieSpecFactory.o \
	${SRC_HOME}/cookie/CookieSpecRegistry.o \
	${SRC_HOME}/cookie/SetCookie2.o \
	${SRC_HOME}/cookie/SetCookie.o \
    ${SRC_HOME}/cookie/SM.o \
	${SRC_HOME}/cookie/params/CookieSpecPNames.o \
	${SRC_HOME}/cookie/params/CookieSpecParamBean.o $(LDFLAGS)
clean:
	$(RM) libcookie.so  ${SRC_HOME}/cookie/ClientCookie.o \
	${SRC_HOME}/cookie/CookieAttributeHandler.o \
	${SRC_HOME}/cookie/Cookie.o \
	${SRC_HOME}/cookie/CookieIdentityComparator.o \
	${SRC_HOME}/cookie/CookieOrigin.o \
	${SRC_HOME}/cookie/CookiePathComparator.o \
	${SRC_HOME}/cookie/CookieSpecFactory.o \
	${SRC_HOME}/cookie/CookieSpecRegistry.o \
	${SRC_HOME}/cookie/SetCookie2.o \
	${SRC_HOME}/cookie/SetCookie.o \
    ${SRC_HOME}/cookie/SM.o \
	${SRC_HOME}/cookie/params/CookieSpecPNames.o \
	${SRC_HOME}/cookie/params/CookieSpecParamBean.o \
	${SRC_HOME}/libs/libcookie.so
install:
	$(CP) libcookie.so ${SRC_HOME}/libs/
