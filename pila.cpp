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
        /*
        nodo* aux = top->anterior;
        aux->anterior->siguiente = top;
        top->anterior = aux->anterior;
        delete aux;

        nodo*aux = top;
        top->anterior->siguiente = top->siguiente;
        top->siguiente->anterior = top->anterior;
        aux->anterior = NULL;
        aux->siguiente = NULL;
        top = top->siguiente;
        delete aux;
         */
        nodo* temp = top;
        top->anterior->siguiente = top->siguiente;
        top->siguiente->anterior = top->anterior;
        top = top->siguiente;
        delete temp;

    }
    return pop->getValor();
}

