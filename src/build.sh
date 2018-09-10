echo rm -f $HOME/httpConnection/src/obj.x86_64/*o 
rm -f $HOME/httpConnection/src/obj.x86_64/*o 

echo g++ -m64 -shared -fPIC -g -c -D_REENTRANT  -o $HOME/httpConnection/src/obj.x86_64/utils.o utils.cc
g++ -m64 -shared -fPIC -g -c -std="c++17" -D_REENTRANT  -o $HOME/httpConnection/src/obj.x86_64/utils.o utils.cc

echo g++ -m64 -shared -fPIC -g -c -D_REENTRANT  -o $HOME/httpConnection/src/obj.x86_64/HttpDateGenerator.o HttpDateGenerator.cc
g++ -m64 -shared -fPIC -g -c -std="c++17" -D_REENTRANT  -o $HOME/httpConnection/src/obj.x86_64/HttpDateGenerator.o HttpDateGenerator.cc

echo g++ -m64 -shared -fPIC -g  -D_REENTRANT  -o $HOME/httpConnection/src/obj.x86_64/libutils.so $HOME/httpConnection/src/obj.x86_64/utils.o $HOME/httpConnection/src/obj.x86_64/HttpDateGenerator.o -lm  -lpthread
g++ -m64 -shared -fPIC -g  -std="c++17" -D_REENTRANT  -o $HOME/httpConnection/src/obj.x86_64/libutils.so $HOME/httpConnection/src/obj.x86_64/utils.o $HOME/httpConnection/src/obj.x86_64/HttpDateGenerator.o -lm  -lpthread

echo g++ -m64 -shared -fPIC -g -c -D_REENTRANT  -o $HOME/httpConnection/src/obj.x86_64/transport.o $HOME/httpConnection/src/transport.cc
g++ -m64 -shared -std="c++17" -fPIC -g -c -D_REENTRANT  -o $HOME/httpConnection/src/obj.x86_64/transport.o $HOME/httpConnection/src/transport.cc

echo g++ -m64 -shared -fPIC -g  -D_REENTRANT  -o $HOME/httpConnection/src/obj.x86_64/libtransport.so obj.x86_64/transport.o -lm  -lnsl -lpthread
g++ -m64 -std="c++17" -shared -fPIC -g  -D_REENTRANT  -o $HOME/httpConnection/src/obj.x86_64/libtransport.so obj.x86_64/transport.o -lm  -lnsl -lpthread

echo g++ -m64 -std="c++11" -I. -g -o $HOME/httpConnection/src/obj.x86_64/httpConnection/src $HOME/httpConnection/src/Main.cc -L$HOME/httpConnection/src/obj.x86_64  -lutils -ltransport -lnsl -lm  -lpthread
g++ -m64 -std="c++17" -I. -I /usr/include -g -o $HOME/httpConnection/src/obj.x86_64/replay $HOME/httpConnection/src/Main.cc -L$HOME/httpConnection/src/obj.x86_64  -lutils -ltransport -lnsl -lm  -lcrypto -lssl -lpthread
