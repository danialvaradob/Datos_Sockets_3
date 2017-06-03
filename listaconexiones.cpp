//
// Created by Daniel Alvarado on 5/18/17.
//

#include "listaconexiones.h"

ListaConexiones::~ListaConexiones() {
    NodoConexion* aux;

    while(primero) {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
    actual = NULL;

}


void ListaConexiones::agregarConexion(int _codigo, int _peso) {

    if (listaVacia()){
        NodoConexion* nuevo = new  NodoConexion( _codigo,  _peso);

        primero = nuevo;
        nuevo->siguiente = primero;
        nuevo->anterior = primero;
        cantidadConexiones++;
    }else{
        NodoConexion* nuevo = new  NodoConexion( _codigo,_peso);
        nuevo->siguiente = primero;
        nuevo->anterior = primero->anterior;
        primero->anterior->siguiente = nuevo;
        primero->anterior = nuevo;
        cantidadConexiones++;
    }
}

int ListaConexiones::largoLista() {
    int cont = 1;
    NodoConexion* aux;
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
int ListaConexiones::getCodMenorConexion() {
    int menorConexion;
    int menorPeso;
    NodoConexion* nodoAux = primero;
    do {
        if (!nodoAux->visitado) {
            menorPeso = nodoAux->peso;
            break;
        }
        nodoAux = nodoAux->siguiente;
    } while (nodoAux != primero);


    NodoConexion* aux = primero;

    do{
        if (aux->peso <= menorPeso && !aux->visitado) {
            menorConexion = aux->codLugar;
            menorPeso = aux->peso;
            //break;
        }
        aux = aux->siguiente;
    } while (aux != primero);
    return menorConexion;

}

int ListaConexiones::getPeso(int _codigo) {
    NodoConexion* aux = primero;
    do {
        if (aux->codLugar == _codigo)
            return aux->peso;
        aux = aux->siguiente;
    } while (aux != primero);
    return 0;
}

void ListaConexiones::visitar(int _codigo) {
    NodoConexion* aux = primero;
    do {
        if (aux->codLugar == _codigo)
            aux->visitado = true;
        aux = aux->siguiente;
    } while (aux != primero);

}

void ListaConexiones::desvisitarConexiones() {
    NodoConexion* aux = primero;
    do {
        aux->visitado = false;
        aux = aux->siguiente;
    } while (aux != primero);

}

int ListaConexiones::getMayorPeso() {
    NodoConexion* aux = primero;
    int mayorPeso = primero->peso;
    do {
        if (mayorPeso < aux->peso){
            mayorPeso = aux->peso;
        }
        aux = aux->siguiente;
    } while (aux != primero);

    return  mayorPeso;
}

bool ListaConexiones::existeConexion(int _codigo) {
    NodoConexion* aux = primero;
    do {
        if (aux->codLugar == _codigo)
            return true;
        aux = aux->siguiente;
    } while(aux != primero);
    return false;
}