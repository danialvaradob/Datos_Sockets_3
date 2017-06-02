//
// Created by Daniel Alvarado on 5/18/17.
//

#ifndef PROGRA_3_LISTALUGARES_H
#define PROGRA_3_LISTALUGARES_H

#include "nodolugar.h"

//LISTA CIRCULAR DOBLE

class ListaLugares {
public:
    ListaLugares() {primero = actual = NULL;}
    ~ListaLugares();

    bool listaVacia() {return primero == NULL;}

    int largoLista();
    void insertarLugar(int _codigo, std::string _nombre);
    bool existeLugar(int _codigo);
    void aumentarCantidadDeSupermercados(int codLugar);
    void getLugarMasSuper(NodoLugar*&_lugarMasSupermercados);
    NodoLugar* getNodoLugar(int _codigo);


    //FUNCIONES UTILIZADAS PARA GRAFOS
    int getCantidadConexiones(int _codLugar);
    NodoLugar* getMenorConexion(NodoLugar* _nodoIncicial); //retorna el nodo menor al cual esta conectado
                                                         // dicho lugar
    void recorridoProfundidad(NodoLugar* _nodoInicial);
    int getNumVertices();

    int getCodigo(int _posicion); //recibe como parametro la posicion de la cual desea el codigo
    void desvisitarTODO();

    void visitarTodasConexiones(int _codigoDeConexion);


    NodoLugar* primero;
    NodoLugar* actual;

};



#endif //PROGRA_3_LISTALUGARES_H
