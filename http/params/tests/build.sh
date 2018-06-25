g++ -g -m64 -std=c++11 -I.. -I../../inc/ -I../../protocol/ -I../../util -o main \
                                             Main.cc \
                                             ../AbstractHttpParams.cc \
                                             ../BasicHttpParams.cc \
                                             ../Value.cc \
                                             ../../HttpVersion.cc \
                                             ../../ProtocolVersion.cc \
                                             ../CoreProtocolPNames.cc \
                                             ../HttpProtocolParams.cc \
                                             ../DefaultedHttpParams.cc \
                                             ../CoreConnectionPNames.cc \
                                             ../HttpConnectionParams.cc \
                                             ../HttpAbstractParamBean.cc \
                                             ../HttpConnectionParamBean.cc \
                                             ../../util/CharArrayBuffer.cc \
                                             ../../protocol/HTTP.cc
