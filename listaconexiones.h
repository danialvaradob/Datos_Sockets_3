//
// Created by Daniel Alvarado on 5/18/17.
//

#ifndef PROGRA_3_LISTACONEXIONES_H
#define PROGRA_3_LISTACONEXIONES_H

#include "nodoconexion.h"


class ListaConexiones {
public:
    ListaConexiones() {primero = actual = NULL; cantidadConexiones = 0;}
    ~ListaConexiones();

    bool listaVacia() {return primero == NULL;}

    int largoLista();
    void agregarConexion(int _codigo, int _peso);
    int getCodMenorConexion();
    int getCantidadConexiones() {return cantidadConexiones;}
    int getPeso(int _codigo); //busca en la lista a ver si existe el codigo y si existe
                                //retorna el peso entre esos dos

    void desvisitarConexiones();

    bool existeConexion(int _codigo);

    void visitar(int _codigo);
    int getMayorPeso();

    NodoConexion* primero;
    NodoConexion* actual;
private:
    friend class ListaLugares;
    int cantidadConexiones;
};


#endif //PROGRA_3_LISTACONEXIONES_H
