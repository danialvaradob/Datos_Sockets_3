//MAIN PROVEEDOR//
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
 
using namespace std;
 
int main()
	{
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
 		
 				while (true){
				
			
				cout<<"||||||||||||||||||||||||||||||||Bienvenido al sistema|||||||||||||||||||||||||||||||||||||||\r\n"<<endl;
				cout<<"Este es el menu principal"<<endl;
				cout<<"Presione 1 para atender ventas"<<endl;
				cout<<"Presione 2 para ver proveedor con mas ventas"<<endl;
				cout<<"Presione 3 para ver producto que m�s se vendi� "<<endl;
				cout<<"Presione 4 para ver productos que rebajaron su stock"<<endl;
				cout<<"Presione 5 para ver categor�a m�s vendida"<<endl;
				cout<<"Presione 6 para ver supermercado con mas ventas"<<endl;
				cout<<"Presione 7 para ver lugar con mas supermercados"<<endl;
				cout<<"Presione 8 para ver lugar que mas vendi�"<<endl;
				cout<<"Presione 9 para ver impresi�n con recorrido preorden de todos los arboles"<<endl;
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
				memset(buffer, 0, sizeof(buffer));
				switch(int_msg){
					case 1:
						while (true){ //Se reciben las solicitued de ventas del servidor
							string venta_msg = "VENTA";
							send(server, venta_msg.c_str(), strlen(msg_char),0);
							cout<<"Esperando venta"<<endl;
							recv(server, buffer, sizeof(buffer), 0);
							cout<<"Venta nueva"<<endl;
							
							string codL, codS, codC, codP = "";
							
						 	int contadorVenta=0;
						 	//char *s = "v;11;55;78;47";
							std::string str(buffer);
						 	
						 	for(char& c : str) {
						 		if (c != ';' && contadorVenta == 1){
						 			codL = codL + c;
								 }
								else if (c != ';' && contadorVenta == 2){
									codS = codS + c;
								}
								else if (c != ';' && contadorVenta == 3){
									codC = codC + c;
								}
								else if (c != ';' && contadorVenta == 4){
									codP = codP + c;
								}
								else if (c == ';'){
									contadorVenta++;
								}
						    	//cout<<c<<endl;
							}
							
							cout<<"Informacion de la venta: "<<endl;
							
							
							cout<<"Codigo del lugar: "<<codL<<endl;
							cout<<"Codigo del supermercado: "<<codS<<endl;
							cout<<"Codigo de la categoria: "<<codC<<endl;
							cout<<"Codigo del producto: "<<codP<<endl;
							memset(buffer, 0, sizeof(buffer));
						break;
					}
					break;
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
						{
						cout<<"Producto con mas ventas"<<endl;
						//cout<<" mas ventas"<<endl;
						string mayorProveedor_msg = "VENTAS PRODUCTO";
						send(server, mayorProveedor_msg.c_str(), strlen(mayorProveedor_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"El producto con mas ventas es "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));
						break;
						//Solicitar proveedor con mas ventas al servidor
						}
						
						//Solicitar producto con mas ventas al servidor
						break;
					case 4:
						cout<<"Productos que rebajaron stock"<<endl;
						//Solicitar productos que rebajaron stock al servidor
						{
						string mayorProveedor_msg = "VENTAS STOCK";
						send(server, mayorProveedor_msg.c_str(), strlen(mayorProveedor_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Los productos que rebajaron su stock son: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						break;
					case 5:
						cout<<"Categoria con mas ventas"<<endl;
						{
						string mayorProveedor_msg = "VENTAS CATEGORIA";
						send(server, mayorProveedor_msg.c_str(), strlen(mayorProveedor_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Categoria que mas vendio: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						//Solicitar categoria con mas ventas al servidor
						break;
					case 6:
						cout<<"Supermercado con mas ventas"<<endl;
						{
						string mayorProveedor_msg = "VENTAS SUPERMERCADO";
						send(server, mayorProveedor_msg.c_str(), strlen(mayorProveedor_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Categoria que mas vendio: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						//Solicitar supermercado con mas ventas al servidor
						break;
					case 7:
						cout<<"Lugar con mas supermercado"<<endl;
						{
						string mayorProveedor_msg = "SUPERMERCADO LUGAR";
						send(server, mayorProveedor_msg.c_str(), strlen(mayorProveedor_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Categoria que mas vendio: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						//Solicitar lugar con mas supermercados al servidor
						break;
					case 8:
						cout<<"Lugar con mas ventas"<<endl;
						{
						string mayorProveedor_msg = "VENTAS LUGAR";
						send(server, mayorProveedor_msg.c_str(), strlen(mayorProveedor_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Categoria que mas vendio: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						//Solicitar lugar con mas ventas al servidor
						break;
					case 9:
						cout<<"Recorrido de arboles"<<endl;
						{
						string otros_msg = "RECORRIDOS";
						send(server, otros_msg.c_str(), strlen(otros_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Categoria que mas vendio: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						//Solicitar recorrido de arboles al servidor
						break;
					case 10:
						{
						string otros_msg = "ELIMINAR C";
						send(server, otros_msg.c_str(), strlen(otros_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Categoria que mas vendio: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						//Eliminar cliente
						cout<<"Eliminar cliente"<<endl;
						break;
					case 11:
						cout<<"Eliminar producto"<<endl;
						//Eliminar producto
						{
						string otros_msg = "ELIMINAR P";
						send(server, otros_msg.c_str(), strlen(otros_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Categoria que mas vendio: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						break;
					case 12:
						cout<<"Lista de adyacencia"<<endl;
						//Solicitar lista de adyacencia
						{
						string otros_msg = "ADYACENCIA";
						send(server, otros_msg.c_str(), strlen(otros_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Categoria que mas vendio: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						break;
					case 13:
						cout<<"Recorrido en profundidad"<<endl;
						{
						string otros_msg = "PROFUNDIDAD";
						send(server, otros_msg.c_str(), strlen(otros_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Profundidad: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						//Solicitar recorrido en profundidad
						break;
					case 14:
						cout<<"Recorrido en anchura"<<endl;
						//Solicitar recorrido en anchura
						{
						string otros_msg = "ANCHURA";
						send(server, otros_msg.c_str(), strlen(otros_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Recorrido anchura: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						break;
					case 15:
						cout<<"Prim"<<endl;
						//Solicitar Prim
						{
						string otros_msg = "PRIM";
						send(server, otros_msg.c_str(), strlen(otros_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Prim: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						break;
					case 16:
						cout<<"Kruskal"<<endl;
						//Solicitar Kruskal
						{
						string otros_msg = "Kruskal";
						send(server, otros_msg.c_str(), strlen(otros_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Kruskal: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						break;
					case 17:
						cout<<"Dijkstra"<<endl;
						//Solicitar Dijkstra
						{
						string otros_msg = "DIJKSTRA";
						send(server, otros_msg.c_str(), strlen(otros_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Dijkstra: "<<buffer<<endl; 
						
						memset(buffer, 0, sizeof(buffer));

						}
						break;
					case 18:
						cout<<"Puntos de articulacion"<<endl;
						//Solicitar puntos de articulacion
						{
						string otros_msg = "ARTICULACION";
						send(server, otros_msg.c_str(), strlen(otros_msg.c_str()),0);
						
						recv(server, buffer, sizeof(buffer), 0);
						cout<<"Puntos de articulacion: "<<buffer<<endl; 
						
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
				cout<<"Presione 3 para ver producto que m�s se vendi� "<<endl;
				cout<<"Presione 4 para ver productos que rebajaron su stock"<<endl;
				cout<<"Presione 5 para ver categor�a m�s vendida"<<endl;
				cout<<"Presione 6 para ver supermercado con mas ventas"<<endl;
				cout<<"Presione 7 para ver lugar con mas supermercados"<<endl;
				cout<<"Presione 8 para ver lugar que mas vendi�"<<endl;
				cout<<"Presione 9 para ver impresi�n con recorrido preorden de todos los arboles"<<endl;
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
//}*/
