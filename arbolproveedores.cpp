//#include <iostream>
#include <sstream>
#include "arbolproveedores.h"


//ARBOL BINARIO DE BUSQUEDA

//+++++++++++++++++++++ Insertar Nodo +++++++++++++++++++++++

void ArbolProveedores::insertarNodoProveedor(int idProveedor,std::string nombre,std::string direccion,int tel) {
    if(raiz==NULL){
        raiz = new NodoProveedor(idProveedor,nombre,direccion,tel);
    }else{
        raiz->insertarProveedor(idProveedor,nombre,direccion,tel);
    }
}

// funcion utilizada para verificar si ya existe un proveedor
bool ArbolProveedores::existeProveedor(int _id, NodoProveedor *_raiz){
    if(_raiz==NULL){
        //cout << "Final de un nodo" << endl;
        return false;
    }else if (_raiz->getID() == _id) {
        //cout << "Encontrado" << endl;
        return true;
    }else{
        //cout << "buscando" << endl;
        return  existeProveedor(_id,_raiz->Hizq) || existeProveedor(_id,_raiz->Hder);
        //existeProveedor(_id,_raiz->Hizq);
        //existeProveedor(_id,_raiz->Hder);

    }
}

//funcion que aumenta la cantidad de ventas de un nodo
void ArbolProveedores::aumentarVentas(int _id, NodoProveedor *_raiz) {
    if (_raiz == NULL) {
        return;
    }
    else if (_raiz->getID() == _id) {
        _raiz->aumentarVentas();

    } else {
        aumentarVentas(_id,_raiz->Hder);
        aumentarVentas(_id,_raiz->Hizq);
    }
}
//retorna el nombre de un _id dado
std::string ArbolProveedores::getNombreProveedor(int _id, NodoProveedor *_raiz) {
    if (_raiz == NULL) {
        return "";
    }
    else if (_raiz->getID() == _id) {
        return _raiz->getNombre();

    } else {
        getNombreProveedor(_id,_raiz->Hder);
        getNombreProveedor(_id,_raiz->Hizq);
    }
}
/*
// Recorridos
void ArbolProveedores::PreordenI(NodoProveedor *R){
    if(R==NULL){
        return;
    }else{
        std::cout<<R->getID()<<std::endl;
        PreordenI(R->Hizq);
        PreordenI(R->Hder);
    }
}

void ArbolProveedores::InordenI(NodoProveedor *R){
    if(R==NULL){
        return;
    }else{
        InordenI(R->Hizq);
        std::cout<<R->getID()<<std::endl;
        InordenI(R->Hder);
    }
}

void ArbolProveedores::PostordenI(NodoProveedor *R){
     if(R==NULL){
        return;
    }else{
        PostordenI(R->Hizq);
        PostordenI(R->Hder);
         std::cout<<R->getID()<<"-";

    }
}

*/
void ArbolProveedores::getNodoProveedor(int _id, NodoProveedor *_raiz, NodoProveedor *&_nuevoNodo) {
    if (_raiz ==NULL) return;
    else if (_raiz->getID() == _id) {
        _nuevoNodo = _raiz;
    } else {
        getNodoProveedor( _id,  _raiz->Hizq,_nuevoNodo);
        getNodoProveedor( _id,  _raiz->Hder,_nuevoNodo);

    }
}

void ArbolProveedores::getNodoProveedorMasVentas(NodoProveedor *_raiz, NodoProveedor *&_nuevoNodo) {
    if (_raiz ==NULL) return;
    else if (_raiz->getCantidadDeVentas() > _nuevoNodo->getCantidadDeVentas()) {
        _nuevoNodo = _raiz;
    } else {
        getNodoProveedorMasVentas( _raiz->Hizq,_nuevoNodo);
        getNodoProveedorMasVentas( _raiz->Hder,_nuevoNodo);

    }
}

void ArbolProveedores::PreordenSocket(NodoProveedor *_raiz, std::string &_string) {
    if (_raiz == NULL) return;
    else {
        std::stringstream flujo;
        std::string nombre;
        flujo << _raiz->getID();
        nombre = flujo.str();
        _string+=nombre+"\n";
        PreordenSocket(_raiz->Hizq, _string);
        PreordenSocket(_raiz->Hder, _string);
    }
}
