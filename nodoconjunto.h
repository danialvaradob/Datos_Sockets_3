//
// Created by MSI GT683 on 6/6/2017.
//

#ifndef PROGRA_3_NODOCONJUNTO_H
#define PROGRA_3_NODOCONJUNTO_H

#include <string>
#include "listalugares.h"

class NodoConjunto {
public:
    NodoConjunto() {
        codigo = 0;
        siguiente = NULL;
        anterior = NULL;
        conSiguiente = NULL;
        conAnterior = NULL;
        visitado = false;

    }

    NodoConjunto(int _codigo) {
        codigo = _codigo;
        siguiente = NULL;
        anterior = NULL;
        conSiguiente = NULL;
        conAnterior = NULL;
        visitado = false;


    }

    int getCodigo() {return codigo;}
    NodoConjunto* getAnteior() {return anterior;}
    NodoConjunto* getSiguiente() {return siguiente;}


    //Conexiones
    void visitar() {visitado = true;}

private:
    bool visitado;
    int codigo;
    NodoConjunto* siguiente;
    NodoConjunto* anterior;
    NodoConjunto* conSiguiente;
    NodoConjunto* conAnterior;



    friend class ListaConjunto;
    friend class ArbolExpansionMinimo;

};


#endif //PROGRA_3_NODOCONJUNTO_H
