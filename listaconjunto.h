//
// Created by MSI GT683 on 7/6/2017.
//

#ifndef PROGRA_3_LISTACONJUNTO_H
#define PROGRA_3_LISTACONJUNTO_H

#include "nodoconjunto.h"

class ListaConjunto {
public:
    ListaConjunto() {primero = NULL;}

    bool listaVacia() {return primero == NULL;}

    int largoLista();
    void insertarConjunto(int _codigo);
    bool existeEnLista(int _codigo);
    bool existeNodoEnConjunto(int codigo, int indice);
    NodoConjunto *getConjunto(int indice);
    void unirConjuntos(int indice1, int indice2);
    void borrarConjunto(int indice);
    void borrarInicio();
    int getIndicedelNodo(int _codigo);
    void insertarNodoEnConjunto(int _codigo, int indice);


    NodoConjunto* primero;

};

// CMAKE
#endif //PROGRA_3_LISTACONJUNTO_H
