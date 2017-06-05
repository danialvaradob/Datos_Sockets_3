#include "nodocliente.h"
#include <sstream>

std::string NodoCliente::toString() {
    std::stringstream flujo;
    std::stringstream flujo2;
    std::stringstream flujo3;
    std::string _idCliente;
    std::string _telefono;
    std::string _bestScore;

    flujo << idx;
    _idCliente = flujo.str();
    flujo2 << telefono;
    _telefono = flujo2.str();
    flujo3 << cantidadDeCompras;
    _bestScore = flujo3.str();

    return "Numero de identificacion: "+_idCliente+"\nNombre del cliente: "+nombre+"\nDireccion del cliente: "+direccion+"\nNumero de telefono: "+_telefono;
}

void NodoCliente::setHIzq(NodoCliente *nodo) {
    izq = nodo;
}

void NodoCliente::setHDer(NodoCliente *nodo) {
    der = nodo;
}

void NodoCliente::setSiguiente(NodoCliente *_siguiente) {
    siguiente = _siguiente;
}

void NodoCliente::setAnterior(NodoCliente *_anterior){
    anterior = _anterior;
}


