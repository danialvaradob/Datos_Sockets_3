#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <exception>
#include <cstdlib>

using namespace std;

int const TAMANHO_BUFFER = 4096;

class SocketClient
{
public:


    SocketClient(char* host, int portNo);

    WSADATA WSAData;
    SOCKET listenFd;
    SOCKADDR_IN addr;

    int TAMANO_BUFFER = TAMANHO_BUFFER;

    char buffer[TAMANHO_BUFFER];

    void readSocket();
    void writeSocket(std::string _message);
    void crearArchivo(std::string _msj);
};

#endif // SOCKETCLIENT_H

