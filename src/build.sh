echo rm -f $HOME//tools/replay/temp/replay/obj.x86_64/*o 
rm -f $HOME//tools/replay/temp/replay/obj.x86_64/*o 

echo g++ -m64 -shared -fPIC -g -c -D_REENTRANT  -o $HOME//tools/replay/temp/replay/obj.x86_64/utils.o utils.cc
g++ -m64 -shared -fPIC -g -c -std="c++11" -D_REENTRANT  -o $HOME//tools/replay/temp/replay/obj.x86_64/utils.o utils.cc

echo g++ -m64 -shared -fPIC -g  -D_REENTRANT  -o $HOME//tools/replay/temp/replay/obj.x86_64/libutils.so $HOME//tools/replay/temp/replay/obj.x86_64/utils.o -lm 
g++ -m64 -shared -fPIC -g  -std="c++11" -D_REENTRANT  -o $HOME//tools/replay/temp/replay/obj.x86_64/libutils.so $HOME//tools/replay/temp/replay/obj.x86_64/utils.o -lm 

echo g++ -m64 -shared -fPIC -g -c -D_REENTRANT  -o $HOME//tools/replay/temp/replay/obj.x86_64/transport.o $HOME//tools/replay/temp/replay/transport.cc
g++ -m64 -shared -std="c++11" -fPIC -g -c -D_REENTRANT  -o $HOME//tools/replay/temp/replay/obj.x86_64/transport.o $HOME//tools/replay/temp/replay/transport.cc

echo g++ -m64 -shared -fPIC -g  -D_REENTRANT  -o $HOME//tools/replay/temp/replay/obj.x86_64/libtransport.so obj.x86_64/transport.o -lm  -lnsl
g++ -m64 -std="c++11" -shared -fPIC -g  -D_REENTRANT  -o $HOME//tools/replay/temp/replay/obj.x86_64/libtransport.so obj.x86_64/transport.o -lm  -lnsl

echo g++ -m64 -std="c++11" -I. -g -o $HOME//tools/replay/temp/replay/obj.x86_64//tools/replay/temp/replay $HOME//tools/replay/temp/replay/Main.cc -L$HOME//tools/replay/temp/replay/obj.x86_64  -lutils -ltransport -lnsl -lm 
g++ -m64 -std="c++11" -I. -I /usr/include -g -o $HOME//tools/replay/temp/replay/obj.x86_64/replay $HOME//tools/replay/temp/replay/Main.cc -L$HOME//tools/replay/temp/replay/obj.x86_64  -lutils -ltransport -lnsl -lm  -lcrypto -lssl
