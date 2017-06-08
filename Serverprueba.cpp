
#include <iostream>
#include <winsock2.h>

 
using namespace std;
 
int main()
{
	
	////////DATOS DEL MAIN////////
	string cod_input;
	
	int cod_input_int;
	string nom_input;
	string cat_input;
	string pro_input;
	bool Desc=false;
	int cod_categoria;
	int int_cant_input;
	string cant_input;
	int precio;
	char yes_no;
	int cod_cliente_input_int;
	string super_input;
	int int_super_input;
	int int_cat_input;
	int int_pro_input;
	bool SALIR=false;
	
	
	
	
	///////FIN DATOS DEL MAIN/////
	
	
    WSADATA WSAData;
 
    SOCKET server, client;
 
    SOCKADDR_IN serverAddr, clientAddr;
 
    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
 
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8889);
 
    bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    listen(server, 0);
 
    cout << "Listening for incoming connections..." << endl;
 //while (true){
 
 
 
    char buffer[1024];
    int clientAddrSize = sizeof(clientAddr);
    if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
    {
        cout << "Client connected!" << endl;
        recv(client, buffer, sizeof(buffer), 0);
        cout<<buffer<<endl;
    	string hola = "Ingrese su codigo";
		send(client, hola.c_str(), strlen(hola.c_str()), 0);
		
		recv(client, buffer, sizeof(buffer), 0);
		
		if (std::atoi(buffer) == 1){
			hola = "CONECTADO";
		send(client, hola.c_str(), strlen(hola.c_str()), 0);
		}
		memset(buffer, 0, sizeof(buffer));
		
		while (true){
			memset(buffer, 0, sizeof(buffer));
			recv(client, buffer, sizeof(buffer), 0);
			cout<<buffer<<endl;
			
			
			hola = "COSAS";
		send(client, hola.c_str(), strlen(hola.c_str()), 0);
		}
       //return 0;
    }
    closesocket(client);
	cout << "Client disconnected." << endl;
    return 0;
   }

