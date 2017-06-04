//
// Created by Daniel Alvarado on 5/20/17.
//

#include "pila.h"
void Pila::push(int _valor) {

    if (vacia()){
        nodo* nuevo = new  nodo( _valor);

        top = nuevo;
        nuevo->siguiente = top;
        nuevo->anterior = top;
    }else{
        nodo* nuevo = new  nodo( _valor);
        nuevo->siguiente = top;
        nuevo->anterior = top->anterior;
        top->anterior->siguiente = nuevo;
        top->anterior = nuevo;

    }
}

int Pila::pop() {
    nodo* pop = top;
    if (top->siguiente == top){
        nodo* temp = top;
        top = NULL;
        delete temp;
    }else{
        nodo* aux = top->anterior;
        aux->anterior->siguiente = top;
        top->anterior = aux->anterior;
        delete aux;
    }
    return pop->getValor();
}

