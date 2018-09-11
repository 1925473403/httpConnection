#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <pthread.h>
#include <string.h>
#include <string>

using namespace std;

void* createListerThread(void *args) {
    std::string host; int port;
    std::cout << "Server Thread(enter host and port): ";
    cin >> host >> port;
    HttpParams *_params = nullptr;
    try {
        InetAddress ip(host);
        ServerSocket serverSocket(port, 10, &ip);
        _params = new BasicHttpParams();
        _params->setIntParameter(CoreConnectionPNames::SO_TIMEOUT, 30000);
        _params->setIntParameter(CoreConnectionPNames::SOCKET_BUFFER_SIZE, 8 * 1024);
        _params->setBooleanParameter(CoreConnectionPNames::STALE_CONNECTION_CHECK, false);
        _params->setBooleanParameter(CoreConnectionPNames::TCP_NODELAY, true);
        _params->setParameter(CoreProtocolPNamesORIGIN_SERVER, "HttpComponents/1.1");
        while (usleep(800) == 0) {
            ClientSocket clientSocket = serverSocket.accept();
            DefaultHttpServerConnection conn = new DefaultHttpServerConnection ();
            _params->ref();
            conn.bind(&clientSocket, _params);
            BasicHttpProcessor httpproc;
            httpproc.addInterceptor(new ResponseDate());
            httpproc.addInterceptor(new ResponseServer());
            httpproc.addInterceptor(new ResponseContent());
            httpproc.addInterceptor(new ResponseConnControl());

            HttpRequestHandlerRegistry *reqistry  = new HttpRequestHandlerRegistry();
            reqistry.register("*", requestHandler);

            HttpService *_httpService = new HttpService(httpproc, new NoConnectionReuseStrategy(), new DefaultHttpResponseFactory());
            _httpService->setParams(_params);
            _httpService->setHandlerResolver(reqistry);


        }
    } catch (const IOException &ex) {
        std::cerr << ex.what() << std::endl;
        std::cerr << "Unable to bind to host " << host << ", port: " << port << std::endl;
        if (_params != nullptr) _params->unref();
        return NULL;
    }
}

int main() {
    pthread_t servertid ;
    if (pthread_create(&servertid, NULL, createListerThread, NULL) < 0) {
        std::cerr << "unable to spawn server thread." << std::endl;
        return -1;
    }
    pthread_join(servertid, NULL);
    return 0;
}
