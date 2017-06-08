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

void ListaConexiones::agregarConexion(int _codigo, int _peso, int codMenor) {

    if (listaVacia()){
        NodoConexion* nuevo = new  NodoConexion( _codigo,  _peso);
		nuevo->codigoUltimaConexion = codMenor;
        primero = nuevo;
        nuevo->siguiente = primero;
        nuevo->anterior = primero;
        cantidadConexiones++;
    }else{
        NodoConexion* nuevo = new  NodoConexion( _codigo,_peso);
        nuevo->codigoUltimaConexion = codMenor;
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

NodoConexion* ListaConexiones::getConexion(int _codigo) {
    NodoConexion* aux = primero;
    do {
        if (aux->codLugar == _codigo)
            return aux;
        aux = aux->siguiente;
    } while (aux != primero);
    return 0;
}

void ListaConexiones::sumarDistTotal(int disTotal, int codMenor) {
    NodoConexion* aux = primero;
    if (aux!=NULL){
    do {
        //if (aux->codLugar == _codigo)
            //return aux;
        aux->codigoUltimaConexion = codMenor;
        aux->peso = aux->peso + disTotal;
        aux = aux->siguiente;
		
    } while (aux != primero);
	}
    return;
}
/*
void ListaConexiones::visitarDijkstra(ListaConexion* nodosResueltos) {
    NodoConexion* aux = nodosResueltos->primero;
    //NodoConexion* aux2 = nodosResueltos->primero;
    do {
        if (aux->codLugar == _codigo)
            aux->visitado = true;
        aux = aux->siguiente;
    } while (aux != primero);

}*/

void ListaConexiones::agregarConexion(NodoConexion*& nuevo) {


    if (listaVacia()){
        //NodoConexion* nuevo = new  NodoConexion( _codigo,  _peso);

        primero = nuevo;
        nuevo->siguiente = primero;
        nuevo->anterior = primero;
        cantidadConexiones++;
    }else{
        //NodoConexion* nuevo = new  NodoConexion( _codigo,_peso);
        nuevo->siguiente = primero;
        nuevo->anterior = primero->anterior;
        primero->anterior->siguiente = nuevo;
        primero->anterior = nuevo;
        cantidadConexiones++;
    }
}


void ListaConexiones::insertarNodosNoResueltos(ListaConexiones* NodosNoResueltos){
	NodoConexion* aux = primero;
	NodoConexion* aux2 = primero;

    do {
    	NodosNoResueltos->agregarConexion(aux);   	
    	aux = aux->siguiente;
    	aux2 = aux2->siguiente;
    }
     while (aux2 != primero);
    return;
}

