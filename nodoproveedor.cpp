#include "nodoproveedor.h"
#include <sstream>

std::string NodoProveedor::toString() {
    std::stringstream flujo;
    std::stringstream flujo1;
    std::stringstream flujo2;
    std::string _codP;
    std::string _telefono;
    std::string _bestScore;

    flujo << numero;
    _codP = flujo.str();
    flujo2 << telefono;
    _telefono = flujo2.str();
    flujo1 << bestScore;
    _bestScore = flujo1.str();


    return "Codigo del proveedor: "+_codP+"\nNombre del proveedor: "+nombre+"\nDireccion del proveedor: "+direccion+"\nTelefono del proveedor: "+_telefono;
}



void NodoProveedor::insertarProveedor(int idProveedor,std::string nombre,std::string direccion,int intTel) {
    if(idProveedor < numero){
        if(Hizq==NULL){
            Hizq = new NodoProveedor(idProveedor,nombre,direccion,intTel);
        }else{
            Hizq->insertarProveedor(idProveedor,nombre,direccion,intTel);
        }
    }else{
        if(Hder==NULL){
            Hder = new NodoProveedor(idProveedor,nombre,direccion,intTel);
        }else{
            Hder->insertarProveedor(idProveedor,nombre,direccion,intTel);
        }
    }
}




int NodoProveedor::getID(){
    return numero;
}

std::string NodoProveedor::getNombre(){
    return nombre;
}

std::string NodoProveedor::getDireccion(){
    return direccion;
}

int NodoProveedor::getTelefono(){
    return telefono;
}

NodoProveedor* NodoProveedor::getAnterior(){
    return anterior;
}
NodoProveedor* NodoProveedor::getSiguiente(){
    return siguiente;
}

void NodoProveedor::setAnterior(NodoProveedor* _anterior){
    anterior = _anterior;
}


void NodoProveedor::setSiguiente(NodoProveedor* _siguiente){
    siguiente = _siguiente;
}

int NodoProveedor::getCantidadDeVentas(){
    return cantidadDeVentas;
}
