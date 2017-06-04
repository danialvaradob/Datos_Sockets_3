//
// Created by Daniel Alvarado on 6/2/17.
//

#ifndef PROGRA_3_NODO_H
#define PROGRA_3_NODO_H

#include <iostream>

class nodo {
public:
    nodo(int _valor) {
        valor =_valor ;
        siguiente = NULL;
        anterior = NULL;
    }
    int getValor() {return valor;}

private:
    int valor;
    nodo* siguiente;
    nodo* anterior;

    friend class Pila;

};


#endif //PROGRA_3_NODO_H
