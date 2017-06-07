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

using namespace std;

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
