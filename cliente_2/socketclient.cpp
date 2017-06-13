#include <sstream>
#include <fstream>
#include <iomanip>
#include "socketclient.h"

using namespace std;




SocketClient::SocketClient(char* host, int portNo)    {


    //portNo = 8888;
    //create client skt

    listenFd = socket(AF_INET, SOCK_STREAM, 0);

    if(listenFd < 0)
    {
        cerr << "Cannot open socket" << endl;
        //return 0;
    }
    server = gethostbyname(host);
    if(server == NULL)
    {
        cerr << "Host does not exist" << endl;
        //return 0;
    }

    bzero((char *) &svrAdd, sizeof(svrAdd));
    svrAdd.sin_family = AF_INET;

    bcopy((char *) server -> h_addr, (char *) &svrAdd.sin_addr.s_addr, server -> h_length);

    svrAdd.sin_port = htons(portNo);

    checker = connect(listenFd,(struct sockaddr *) &svrAdd, sizeof(svrAdd));
    writeSocket("CLIENTE_2");
    readSocket();

}

void SocketClient::writeSocket(std::string _message) {
    send(listenFd,_message.c_str() , strlen(_message.c_str()),0);

}

void SocketClient::readSocket() {
    memset(buffer, 0, sizeof(buffer));
    recv(listenFd, buffer, TAMANO_BUFFER - 1,0);


}

void SocketClient::crearArchivo(string _msj){
    std::string resueltos;
    std::string noresueltos;
    std::string distminima;
    std::string disttotal;
    std::string ultimaconexion;
    std::string ruta;


    std::istringstream iss(_msj);
    std::string token;
    std::getline(iss, token, ' ');
    resueltos = token;

    std::getline(iss, token, ' ');
    noresueltos = token;

    std::getline(iss, token, ' ');
    distminima = token;

    std::getline(iss, token, ' ');
    disttotal = token;

    std::getline(iss, token, ' ');
    ultimaconexion = token;

    std::getline(iss, token, ' ');
    ruta = token;


    //std::cout<<"LALALA "<<ruta<<std::endl;

    std::ofstream myfile;
    myfile.open ("Dijkstra.txt");
    myfile << "---------------------------------------------------------------\n";
    myfile << "---------------------------------------------------------------\n";
    myfile<<"Nodo resuelto"<<std::setw(100)<<"Nodo no-resuelto"<<std::setw(100)<<"Distancia minima"<<std::setw(100)<<"Distancia total"<<std::setw(100)<<"Ultima conexion"<<std::endl;



    std::istringstream iss0 (resueltos);
    std::istringstream iss1 (noresueltos);
    std::istringstream iss2 (distminima);
    std::istringstream iss3 (disttotal);
    std::istringstream iss4 (ultimaconexion);
    while (true){


        std::getline(iss0, token, ';');
        myfile << std::left<<std::setw(50) <<token << std::setw(50) << "      ";
        std::cout << token << std::endl;


        std::getline(iss1, token, ';');
        myfile << std::setw(50) << token << std::setw(50) << "      ";
        std::cout << token << std::endl;


        std::getline(iss2, token, ';');
        myfile << std::left<< std::setw(50) << token << std::setw(50) << "      ";
        std::cout << token << std::endl;



        std::getline(iss3, token, ';');
        myfile<< std::left << std::setw(50) << token << std::setw(50) << "      ";
        std::cout << token << std::endl;


        std::getline(iss4, token, ';');
        myfile << std::left<< std::setw(50) << token << "      "<<std::endl;
        myfile <<std::endl<<std::endl;;
        std::cout << token << std::endl;

        if (token == "$"){

            myfile << "La ruta es: " <<ruta;
            break;
        }
    }
    myfile.close();
}

