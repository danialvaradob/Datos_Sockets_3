#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H
#include <iostream>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
using namespace std;

int const TAMANHO_BUFFER = 4096;

class SocketClient
{
public:


    SocketClient(char* host, int portNo);

    int TAMANO_BUFFER = TAMANHO_BUFFER;
        int listenFd;
        int checker;
        struct sockaddr_in svrAdd;
        struct hostent *server;
        char buffer[TAMANHO_BUFFER];

    void readSocket();
    void writeSocket(std::string _message);
    void crearArchivo(std::string _msj);
};

#endif // SOCKETCLIENT_H
