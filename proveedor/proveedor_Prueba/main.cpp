

//MAIN PROVEEDOR//
#include <iostream>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
/*
#include <iostream>
#include <fstream>
#include <cstring>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>

//using namespace std;

#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <exception>
#include <cstdlib>

*/
const char* host = "127.0.0.1";
int const TAMANHO_BUFFER = 2048;

using namespace std;

int main(){
    //
    /*
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // replace the ip with your futur server ip address. If server AND client are running on the same computer, you can use the local ip 127.0.0.1
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8889);

    connect(server, (SOCKADDR *)&addr, sizeof(addr));
    //cout << "Connected to server!" << endl;
     string msg;
     const char *msg_char;
     char buffer[1024];
     */

    int server, portNo;
    bool loop = false;
    struct sockaddr_in svrAdd;
    struct hostent *server1;
    char buffer[TAMANHO_BUFFER];


    portNo = 8889;
    //create client skt
    server = socket(AF_INET, SOCK_STREAM, 0);
    if(server < 0)
    {
        cerr << "Cannot open socket" << endl;
        return 0;
    }
    server1 = gethostbyname(host);
    if(server1 == NULL)
    {
        cerr << "Host does not exist" << endl;
        return 0;
    }

    bzero((char *) &svrAdd, sizeof(svrAdd));
    svrAdd.sin_family = AF_INET;
    bcopy((char *) server1 -> h_addr, (char *) &svrAdd.sin_addr.s_addr, server1 -> h_length);
    svrAdd.sin_port = htons(portNo);
    int checker = connect(server,(struct sockaddr *) &svrAdd, sizeof(svrAdd));
    if (checker < 0)
    {
        cerr << "Cannot connect!" << endl;
        return 0;
    }

    string msg;
    const char *msg_char;

    string proveedor = "PROVEEDOR";
    send(server, proveedor.c_str(), strlen(proveedor.c_str()),0);

    recv(server, buffer, sizeof(buffer), 0);
    cout<<buffer<<endl;

    for (;;){


        //std::cout<<"Ingrese su codigo: "<<endl;
        std::getline(std::cin, msg);
        msg_char = msg.c_str();
        send(server, msg_char, strlen(msg_char),0);
        memset(buffer, 0, sizeof(buffer));

        recv(server, buffer, sizeof(buffer), 0);
        cout<<buffer<<endl;
        if (std::string (buffer) == "CONECTADO"){
            std::string msg1 = "Gracias";

            //send(server,msg1.c_str(),strlen(msg1.c_str()),0);

            while (true){


                cout<<"||||||||||||||||||||||||||||||||Bienvenido al sistema|||||||||||||||||||||||||||||||||||||||\r\n"<<endl;
                cout<<"Este es el menu principal"<<endl;
                cout<<"Presione 0 para verificar un codigo"<<endl;
                cout<<"Presione 1 para atender ventas"<<endl;
                cout<<"Presione 2 para ver proveedor con mas ventas"<<endl;
                cout<<"Presione 3 para ver producto que más se vendió "<<endl;
                cout<<"Presione 4 para ver productos que rebajaron su stock"<<endl;
                cout<<"Presione 5 para ver categoría más vendida"<<endl;
                cout<<"Presione 6 para ver supermercado con mas ventas"<<endl;
                cout<<"Presione 7 para ver lugar con mas supermercados"<<endl;
                cout<<"Presione 8 para ver lugar que mas vendió"<<endl;
                cout<<"Presione 9 para ver impresión con recorrido preorden de todos los arboles"<<endl;
                cout<<"Presione 10 para eliminar cliente"<<endl;
                cout<<"Presione 11 para eliminar producto"<<endl;
                cout<<"Presione 12 para ver lista de adyacencia"<<endl;
                cout<<"Presione 13 para ver recorrido en profundidad"<<endl;
                cout<<"Presione 14 para ver recorrido en anchura"<<endl;
                cout<<"Presione 15 para ver Prim"<<endl;
                cout<<"Presione 16 para ver Kruskal"<<endl;
                cout<<"Presione 17 para ver Dijkstra"<<endl;
                cout<<"Presione 18 para ver Puntos de articulacion"<<endl;
                cout<<"Respuesta: ";
                std::getline(std::cin, msg);
                msg_char = msg.c_str(); //Convertir el string a constant char*
                int int_msg = std::stoi(msg);
                memset(buffer, 0, sizeof(buffer));
                switch(int_msg){
                    case 0:
                    { 	memset(buffer, 0, sizeof(buffer));
                        cout<<"ESPERANDO EL CODIGO"<<endl;
                        recv(server, buffer, sizeof(buffer), 0);

                        std::string tester (buffer);
                        cout << tester << "\nDesea verificar?";
                        fgets(buffer,TAMANHO_BUFFER,stdin);
                        send(server, buffer, strlen(buffer),0);



                        break;
                    }

                    case 1:
                    { 	memset(buffer, 0, sizeof(buffer));
                        cout<<"ESPERANDO una venta"<<endl;
                        recv(server, buffer, sizeof(buffer), 0);

                        std::string tester (buffer);
                        cout << tester << " recibido\nDesea verificar codigos?";
                        fgets(buffer,TAMANHO_BUFFER,stdin);
                        send(server, buffer, strlen(buffer),0);



                        break;
                    }


                    case 2:
                    {
                        memset(buffer, 0, sizeof(buffer));
                        cout<<"Proveedor mas ventas"<<endl;
                        string mayorProveedor_msg = "VENTAS PROVEEDOR";
                        send(server, mayorProveedor_msg.c_str(), strlen(mayorProveedor_msg.c_str()),0);

                        recv(server, buffer, sizeof(buffer), 0);
                        cout<<"El proveedor con mas ventas es "<<buffer<<endl;

                        memset(buffer, 0, sizeof(buffer));
                        break;
                        //Solicitar proveedor con mas ventas al servidor
                    }

                    case 3:
                    {memset(buffer, 0, sizeof(buffer));
                        cout<<"Producto con mas ventas"<<endl;


                        recv(server, buffer, sizeof(buffer), 0);
                        cout<<"El producto con mas ventas es "<<buffer<<endl;
                        fgets(buffer,TAMANHO_BUFFER,stdin);
                        send(server, buffer, strlen(buffer),0);

                        memset(buffer, 0, sizeof(buffer));
                        break;
                        //Solicitar proveedor con mas ventas al servidor
                    }

                        //Solicitar producto con mas ventas al servidor
                        break;
                    case 4:
                        cout<<"Productos que rebajaron stock"<<endl;
                        //Solicitar productos que rebajaron stock al servidor
                        {memset(buffer, 0, sizeof(buffer));


                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Los productos que rebajaron su stock son: "<<buffer<<endl;

                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);

                            memset(buffer, 0, sizeof(buffer));

                        }
                        break;
                    case 5:
                        cout<<"Categoria con mas ventas"<<endl;
                        {memset(buffer, 0, sizeof(buffer));


                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Categoria que mas vendio: "<<buffer<<endl;

                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);

                            memset(buffer, 0, sizeof(buffer));

                        }
                        //Solicitar categoria con mas ventas al servidor
                        break;
                    case 6:
                        cout<<"Supermercado con mas ventas"<<endl;
                        {memset(buffer, 0, sizeof(buffer));


                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Categoria que mas vendio: "<<buffer<<endl;

                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);

                            memset(buffer, 0, sizeof(buffer));

                        }
                        //Solicitar supermercado con mas ventas al servidor
                        break;
                    case 7:
                        cout<<"Lugar con mas supermercado"<<endl;
                        {memset(buffer, 0, sizeof(buffer));

                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Categoria que mas vendio: "<<buffer<<endl;
                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);

                            memset(buffer, 0, sizeof(buffer));

                        }
                        //Solicitar lugar con mas supermercados al servidor
                        break;
                    case 8:
                        cout<<"Lugar con mas ventas"<<endl;
                        {memset(buffer, 0, sizeof(buffer));


                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Categoria que mas vendio: "<<buffer<<endl;
                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);

                            memset(buffer, 0, sizeof(buffer));

                        }
                        //Solicitar lugar con mas ventas al servidor
                        break;
                    case 9:
                        cout<<"Recorrido de arboles"<<endl;
                        {memset(buffer, 0, sizeof(buffer));
                            string otros_msg = "RECORRIDOS";
                            //send(server, otros_msg.c_str(), strlen(otros_msg.c_str()),0);

                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Categoria que mas vendio: "<<buffer<<endl;
                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);

                            memset(buffer, 0, sizeof(buffer));

                        }
                        //Solicitar recorrido de arboles al servidor
                        break;
                    case 10:
                    {memset(buffer, 0, sizeof(buffer));
                        string otros_msg = "ELIMINAR C";


                        recv(server, buffer, sizeof(buffer), 0);
                        cout<<"Categoria que mas vendio: "<<buffer<<endl;
                        fgets(buffer,TAMANHO_BUFFER,stdin);
                        send(server, buffer, strlen(buffer),0);

                        memset(buffer, 0, sizeof(buffer));

                    }
                        //Eliminar cliente
                        cout<<"Eliminar cliente"<<endl;
                        break;
                    case 11:
                        cout<<"Eliminar producto"<<endl;
                        //Eliminar producto
                        {memset(buffer, 0, sizeof(buffer));


                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Categoria que mas vendio: "<<buffer<<endl;
                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);

                            memset(buffer, 0, sizeof(buffer));

                        }
                        break;
                    case 12:
                        cout<<"Lista de adyacencia"<<endl;
                        //Solicitar lista de adyacencia
                        {memset(buffer, 0, sizeof(buffer));


                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Categoria que mas vendio: "<<buffer<<endl;

                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);



                            memset(buffer, 0, sizeof(buffer));

                        }
                        break;
                    case 13:
                        cout<<"Recorrido en profundidad"<<endl;
                        {memset(buffer, 0, sizeof(buffer));


                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Profundidad: "<<buffer<<endl;
                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);

                            memset(buffer, 0, sizeof(buffer));

                        }
                        //Solicitar recorrido en profundidad
                        break;
                    case 14:
                        cout<<"Recorrido en anchura"<<endl;
                        //Solicitar recorrido en anchura
                        {memset(buffer, 0, sizeof(buffer));

                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Recorrido anchura: "<<buffer<<endl;
                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);

                            memset(buffer, 0, sizeof(buffer));

                        }
                        break;
                    case 15:
                        cout<<"Prim"<<endl;
                        //Solicitar Prim
                        {memset(buffer, 0, sizeof(buffer));


                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Prim: "<<buffer<<endl;
                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);

                            memset(buffer, 0, sizeof(buffer));

                        }
                        break;
                    case 16:
                        cout<<"Kruskal"<<endl;
                        //Solicitar Kruskal
                        {memset(buffer, 0, sizeof(buffer));
                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Kruskal: "<<buffer<<endl;

                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);

                            memset(buffer, 0, sizeof(buffer));

                        }
                        break;
                    case 17:
                        cout<<"Dijkstra"<<endl;
                        //Solicitar Dijkstra
                        {memset(buffer, 0, sizeof(buffer));

                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Dijkstra: "<<buffer<<endl;


                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);

                            memset(buffer, 0, sizeof(buffer));

                        }
                        break;
                    case 18:
                        cout<<"Puntos de articulacion"<<endl;
                        //Solicitar puntos de articulacion
                        {memset(buffer, 0, sizeof(buffer));


                            recv(server, buffer, sizeof(buffer), 0);
                            cout<<"Puntos de articulacion: "<<buffer<<endl;

                            fgets(buffer,TAMANHO_BUFFER,stdin);
                            send(server, buffer, strlen(buffer),0);

                            memset(buffer, 0, sizeof(buffer));

                        }
                        break;

                        cout<<"Opcion invalida"<<endl;


                }
            }
        }

    }


    return 0;
}

//closesocket(server);
//WSACleanup();
//cout << "Socket closed." << endl << endl;

/*
int main(){
	bool servidorConectado = true; //Esto se cambia en el socket
	bool proveedorValido=true;

	string msg;
 	const char *msg_char;
 	char buffer[1024];

	if (servidorConectado){
		std::cout<<"Ingrese su codigo: "<<endl;


		std::getline(std::cin, msg);
		msg_char = msg.c_str(); //Convertir el string a constant char*

		//Enviar al servidor msg_char
		if (proveedorValido){

			while (true){

				cout<<"||||||||||||||||||||||||||||||||Bienvenido al sistema|||||||||||||||||||||||||||||||||||||||\r\n"<<endl;
				cout<<"Este es el menu principal"<<endl;
				cout<<"Presione 1 para atender ventas"<<endl;
				cout<<"Presione 2 para ver proveedor con mas ventas"<<endl;
				cout<<"Presione 3 para ver producto que más se vendió "<<endl;
				cout<<"Presione 4 para ver productos que rebajaron su stock"<<endl;
				cout<<"Presione 5 para ver categoría más vendida"<<endl;
				cout<<"Presione 6 para ver supermercado con mas ventas"<<endl;
				cout<<"Presione 7 para ver lugar con mas supermercados"<<endl;
				cout<<"Presione 8 para ver lugar que mas vendió"<<endl;
				cout<<"Presione 9 para ver impresión con recorrido preorden de todos los arboles"<<endl;
				cout<<"Presione 10 para eliminar cliente"<<endl;
				cout<<"Presione 11 para eliminar producto"<<endl;
				cout<<"Presione 12 para ver lista de adyacencia"<<endl;
				cout<<"Presione 13 para ver recorrido en profundidad"<<endl;
				cout<<"Presione 14 para ver recorrido en anchura"<<endl;
				cout<<"Presione 15 para ver Prim"<<endl;
				cout<<"Presione 16 para ver Kruskal"<<endl;
				cout<<"Presione 17 para ver Dijkstra"<<endl;
				cout<<"Presione 18 para ver Puntos de articulacion"<<endl;

				std::getline(std::cin, msg);
				msg_char = msg.c_str(); //Convertir el string a constant char*
				int int_msg = std::stoi(msg);

				switch(int_msg){
					case 1:
						while (true){ //Se reciben las solicitued de ventas del servidor
						break;
					}
					break;
					case 2:
						cout<<"Proveedor mas ventas"<<endl;
						//Solicitar proveedor con mas ventas al servidor
						break;
					case 3:
						cout<<"Producto con mas ventas"<<endl;
						//Solicitar producto con mas ventas al servidor
						break;
					case 4:
						cout<<"Productos que rebajaron stock"<<endl;
						//Solicitar productos que rebajaron stock al servidor
						break;
					case 5:
						cout<<"Categoria con mas ventas"<<endl;
						//Solicitar categoria con mas ventas al servidor
						break;
					case 6:
						cout<<"Supermercado con mas ventas"<<endl;
						//Solicitar supermercado con mas ventas al servidor
						break;
					case 7:
						cout<<"Lugar con mas supermercado"<<endl;
						//Solicitar lugar con mas supermercados al servidor
						break;
					case 8:
						cout<<"Lugar con mas ventas"<<endl;
						//Solicitar lugar con mas ventas al servidor
						break;
					case 9:
						cout<<"Recorrido de arboles"<<endl;
						//Solicitar recorrido de arboles al servidor
						break;
					case 10:
						//Eliminar cliente
						cout<<"Eliminar cliente"<<endl;
						break;
					case 11:
						cout<<"Eliminar producto"<<endl;
						//Eliminar producto
						break;
					case 12:
						cout<<"Lista de adyacencia"<<endl;
						//Solicitar lista de adyacencia
						break;
					case 13:
						cout<<"Recorrido en profundidad"<<endl;
						//Solicitar recorrido en profundidad
						break;
					case 14:
						cout<<"Recorrido en anchura"<<endl;
						//Solicitar recorrido en anchura
						break;
					case 15:
						cout<<"Prim"<<endl;
						//Solicitar Prim
						break;
					case 16:
						cout<<"Kruskal"<<endl;
						//Solicitar Kruskal
						break;
					case 17:
						cout<<"Dijkstra"<<endl;
						//Solicitar Dijkstra
						break;
					case 18:
						cout<<"Puntos de articulacion"<<endl;
						//Solicitar puntos de articulacion
						break;

					cout<<"Opcion invalida"<<endl;


				}
			}

			}

		}
	return 0;

	}

//	return 0;
//}

/*
#include <iostream>
#include <string.h>
#include <cstring>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
const char* host = "127.0.0.1";
int const TAMANHO_BUFFER = 1024;

int main (int argc, char* argv[])
{
    int listenFd, portNo;
    bool loop = false;
    struct sockaddr_in svrAdd;
    struct hostent *server;
    char buffer[TAMANHO_BUFFER];


    portNo = 8889;
    //create client skt
    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenFd < 0)
    {
        cerr << "Cannot open socket" << endl;
        return 0;
    }
    server = gethostbyname(host);
    if(server == NULL)
    {
        cerr << "Host does not exist" << endl;
        return 0;
    }

    bzero((char *) &svrAdd, sizeof(svrAdd));
    svrAdd.sin_family = AF_INET;
    bcopy((char *) server -> h_addr, (char *) &svrAdd.sin_addr.s_addr, server -> h_length);
    svrAdd.sin_port = htons(portNo);
    int checker = connect(listenFd,(struct sockaddr *) &svrAdd, sizeof(svrAdd));
    if (checker < 0)
    {
        cerr << "Cannot connect!" << endl;
        return 0;
    }
    bool bandera = true;

    std::string proveedor = "PROVEEDOR";

    //send stuff to server
    for(;;)
    {
        //cin.clear();
        //cin.ignore(256, '\n');
        //cin.getline(buffer, TAMANHO_BUFFER);
        if (bandera) {
            write(listenFd, proveedor.c_str(), strlen(proveedor.c_str()));
            bandera = false;
            bzero(buffer, TAMANHO_BUFFER);
            read(listenFd,buffer,TAMANHO_BUFFER-1);
            printf("%s\n",buffer);
            cout << "Respuesta: ";
            bzero(buffer, TAMANHO_BUFFER);
            fgets(buffer,TAMANHO_BUFFER,stdin);
            write(listenFd, buffer, strlen(buffer));

            bzero(buffer, TAMANHO_BUFFER);
            read(listenFd,buffer,TAMANHO_BUFFER-1);
            printf("%s\n",buffer);
            //write de tramite :)
            write(listenFd, buffer, strlen(buffer));






        } else {

            //bzero(buffer, TAMANHO_BUFFER);
            read(listenFd,buffer,TAMANHO_BUFFER-1);
            printf("%s\n",buffer);
            cout << "Enter stuff: ";
            bzero(buffer, TAMANHO_BUFFER);
            fgets(buffer,TAMANHO_BUFFER,stdin);
            write(listenFd, buffer, strlen(buffer));

            bzero(buffer, TAMANHO_BUFFER);
            read(listenFd,buffer,TAMANHO_BUFFER-1);

            bzero(buffer, TAMANHO_BUFFER);
            read(listenFd,buffer,TAMANHO_BUFFER-1);
            printf("%s\n",buffer);


        }

    }
}

void *task1 (void *dummyPt) {

}


*/