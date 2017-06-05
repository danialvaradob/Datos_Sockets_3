#ifndef ARBOLPROVEEDORES_H
#define ARBOLPROVEEDORES_H
#include "nodoproveedor.h"



//ARBOL BINARIO DE BUSQUEDA

class ArbolProveedores
{
public:

    NodoProveedor *raiz;

    ArbolProveedores():raiz(NULL){};

   //++++Insersion al arbol+++++++++++++++++++++

    void insertarNodoProveedor(int idProveedor,std::string nombre,std::string direccion,int tel);
    //++++++++++++ Ordenes ++++++++++++++++++++++++
    void PreordenI(NodoProveedor *R);
    void PreordenSocket(NodoProveedor *_raiz, std::string &string);
    void InordenI(NodoProveedor *R);
    void PostordenI(NodoProveedor *R);

    //+++++++++++ Recorrido +++++++++++++
    int RecorrerV(NodoProveedor * R);

    //¿Existe proveedor?
    bool existeProveedor(int _id, NodoProveedor* _raiz);
    //Aumenta las ventas de un proveedor determinado
    void aumentarVentas(int _id, NodoProveedor *_raiz);

    std::string getNombreProveedor(int _id, NodoProveedor *_raiz);
    void getNodoProveedor(int _id,NodoProveedor *_raiz, NodoProveedor* &_nuevoNodo);
    void getNodoProveedorMasVentas(NodoProveedor *_raiz, NodoProveedor *&_nuevoNodo);

    bool encontrado = false;
};

#endif // ARBOLPROVEEDORES_H
