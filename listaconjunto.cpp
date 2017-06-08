//
// Created by MSI GT683 on 7/6/2017.
//

#include "listaconjunto.h"


void ListaConjunto::insertarConjunto(int _codigo) {

    if (listaVacia()){
        NodoConjunto* nuevo = new  NodoConjunto( _codigo);

        primero = nuevo;
        nuevo->siguiente = primero;
        nuevo->anterior = primero;
        nuevo->conAnterior = primero;
        nuevo->conAnterior = primero;
    }else{
        NodoConjunto* nuevo = new  NodoConjunto( _codigo);
        nuevo->siguiente = primero->anterior->siguiente;
        nuevo->anterior = primero->anterior;
        nuevo->conAnterior = nuevo;
        nuevo->conSiguiente = nuevo;
        primero->anterior->siguiente = nuevo;
        primero->anterior = nuevo;

    }
}

void ListaConjunto::insertarNodoEnConjunto(int _codigo, int indice) {

    if (listaVacia()){
        NodoConjunto* nuevo = new  NodoConjunto( _codigo);
        primero = nuevo;
        nuevo->siguiente = primero;
        nuevo->anterior = primero;
        nuevo->conSiguiente = primero;
        nuevo->conAnterior = primero;
    }else{
        NodoConjunto *aux = primero;
        for(int h = 1; h<indice; h++){
            aux = aux->siguiente;
        }
        NodoConjunto* nuevo = new  NodoConjunto( _codigo);
        nuevo->conSiguiente = aux;
        nuevo->conAnterior = aux->conAnterior;
        aux->conAnterior->conSiguiente = nuevo;
        aux->conAnterior = nuevo;
    }
}

int ListaConjunto::largoLista() {
    int cont = 1;
    NodoConjunto* aux;
    aux = primero;
    if(listaVacia()){
        return cont;
    }else{
        while(aux->siguiente != primero){
            aux=aux->siguiente;
            cont++;
        }
        return cont;
    }
}

bool ListaConjunto::existeEnLista(int _codigo) {
    NodoConjunto* aux = primero;
    if (listaVacia()) return false;
    do{
        NodoConjunto* temp = aux;
        do{
            if (temp->codigo == _codigo) return true;
            temp = temp->conSiguiente;
        }while(temp != aux);
        aux = aux->siguiente;
    }while(aux!= primero);
    return false;
}

bool ListaConjunto::existeNodoEnConjunto(int _codigo, int indice) {
    NodoConjunto* aux = primero;
    bool existe = false;
    int i = 1;
    if (listaVacia()) return false;
    for(i; i<indice; i++){
        aux = aux->siguiente;
    }
    NodoConjunto* temp = aux;
    do{
        if (temp->codigo == _codigo) return true;
        temp = temp->conSiguiente;
    }while(temp != aux);
}

NodoConjunto *ListaConjunto::getConjunto(int indice){
    NodoConjunto* aux = primero;
    int i = 1;
    if (listaVacia()) return NULL;
    for(i; i<indice; i++){
        aux = aux->siguiente;
    }
    return aux;
}

void ListaConjunto::unirConjuntos(int indice1, int indice2) {
    NodoConjunto *conjunto =  getConjunto(indice2);
    NodoConjunto *aux = conjunto;
    do{
        insertarNodoEnConjunto(aux->codigo, indice1);
        aux = aux->conSiguiente;
    }while(aux!= conjunto);
    borrarConjunto(indice2);

}

void ListaConjunto::borrarInicio()
{
    if (listaVacia()){}
    else
    {
        if (primero->siguiente == primero)
        {
            NodoConjunto *temp= primero;
            primero= NULL;
            delete temp;
        }
        else
        {
            NodoConjunto *aux = primero;
            NodoConjunto *temp= primero;
            while (aux->siguiente!=primero)
                aux= aux->siguiente;
            aux->siguiente=primero->siguiente;
            primero=primero->siguiente;
            primero->anterior=aux;
            delete temp;
        }
    }
}

void ListaConjunto::borrarConjunto(int indice) {
    if(indice==1){
        borrarInicio();
    }
    else{
        NodoConjunto* aux = primero;
        for(int i=2; i<indice; i++){
            aux = aux->siguiente;
        }
        NodoConjunto *temp = aux->siguiente;
        aux->siguiente = aux->siguiente->siguiente;
        aux->siguiente->siguiente->anterior = aux;
        delete(temp);
    }
}

int ListaConjunto::getIndicedelNodo(int _codigo) {
    NodoConjunto* aux = primero;
    int i = 1;
    if (listaVacia()) return 0;
    do{
        NodoConjunto* temp = aux;
        do{
            if (temp->codigo == _codigo) return i;
            temp = temp->conSiguiente;
        }while(temp != aux);
        i++;
        aux = aux->siguiente;
    }while(aux!= primero);
    return 0;
}

