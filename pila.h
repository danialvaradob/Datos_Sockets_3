//
// Created by Daniel Alvarado on 5/20/17.
//

#ifndef PROGRA_3_PILA_H
#define PROGRA_3_PILA_H

#include "nodo.h"

class Pila {
public:
    Pila() {top = NULL;}

    void push(int _valor);
    bool vacia() {return top == NULL;};
    nodo* pop();

private:
    nodo*  top;
    friend class ListaLugares;




};


#endif //PROGRA_3_PILA_H
