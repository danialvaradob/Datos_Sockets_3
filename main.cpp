#include <iostream>
#include <fstream>
//#include "listalugares.h"
#include "arbolexpansion.h"
void leerArchLugares(ListaLugares * _lugares){
    std::string nombreArchivo = "Lugares.txt";

    std::ifstream archivoEntrada;
    std::string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, std::ios::in);

    if (archivoEntrada.fail()) {
        std::cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << std::endl;
    }

    while (archivoEntrada >> lineaEnArchivo){
        char * lineaValores = new char[lineaEnArchivo.length()+1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        std::string id(std::strtok (lineaValores, ";"));
        std::string nombre(std::strtok (NULL, ";"));

        // ... crear el nodo
        //cout << id << "," << nombre << "," << direccion << "," << telefono << endl;
        int codigoL = atoi(id.c_str());


        if (_lugares->existeLugar(codigoL))
            continue;
        else{
            std::cout << "Codigo Lugares: " << id << std::endl;
            _lugares->insertarLugar(codigoL,nombre);
        }
    }
    archivoEntrada.close();
    std::cout << _lugares->largoLista() << std::endl;
}

void leerArchConexiones(ListaLugares* _listaLugares) {
    std::string nombreArchivo = "Conexiones.txt";

    std::ifstream archivoEntrada;
    std::string lineaEnArchivo;

    archivoEntrada.open(nombreArchivo, std::ios::in);

    if (archivoEntrada.fail()) {
        std::cout << "Problemas al intentar abrir el archivo: " << nombreArchivo << std::endl;
    }

    while (archivoEntrada >> lineaEnArchivo) {
        char *lineaValores = new char[lineaEnArchivo.length() + 1];
        strcpy(lineaValores, lineaEnArchivo.c_str());


        std::string codLugar(std::strtok(lineaValores, ";"));
        std::string codConexion(std::strtok(NULL, ";"));
        std::string peso(std::strtok(NULL, ";"));

        // ... crear el nodo
        std::cout << codLugar << "," << codConexion << "," << peso << std::endl;
        int codigoL = atoi(codLugar.c_str());
        int codConex = atoi(codConexion.c_str());
        int pesoI = atoi(peso.c_str());

        NodoLugar *lugar = _listaLugares->getNodoLugar(codigoL);
        lugar->getConexiones()->agregarConexion(codConex, pesoI);
    }


}

int main() {

    ListaLugares* _listaLugares = new ListaLugares();
    leerArchLugares(_listaLugares);
    leerArchConexiones(_listaLugares);
    //ArbolExpansionMinimo* arbolExpansionMinimo = new ArbolExpansionMinimo(_listaLugares);
    //int min = arbolExpansionMinimo->arbolExpancionPrim(_listaLugares);
    ArbolExpansionMinimo* arbol = new ArbolExpansionMinimo();
    arbol->prim(_listaLugares,78);




    return 0;
}
