#ifndef ARBOLPRODUCTOS_H
#define ARBOLPRODUCTOS_H

#include "nodoproducto.h"

//ARBOL AA

class ArbolProductos
{
public:

    NodoProducto* raiz;

    ArbolProductos():raiz(NULL){}
    //Funcion utilizada para ir agregando nodos
    void buscar(int _codigoProducto, int _codigoCategoria, std::string _nombreProducto, double _precioPorUnidad, int _cantidadEnStock);
    void girar(NodoProducto  *temp);   //se utiliza skew en ingles
    bool dividir(NodoProducto  *temp); //se utiliza split en ingles
    void balancear(NodoProducto * temp);  //se utiliza rebal en ingles
    NodoProducto* insertarNodo(NodoProducto * temp, NodoProducto * ins); // se utiliza insert en ingles
    void print(NodoProducto*H);
    NodoProducto *eliminar(NodoProducto* _raiz,int _codigoProducto); //estaba intenandola
    NodoProducto *decrementarNivel(NodoProducto* _raiz);

    void PreordenSocket(NodoProducto *_raiz, std::string &_string);

    //void preordenI(NodoProducto *R); //funcion utilizada para recorrer el arbol e ir imprimiendo en preorden la info


    // retorna true si en un determinado arbol de productos existe (el arbol de productos todos tienen la misma categoria)
    bool existeProducto(NodoProducto *_raiz,int codProducto);
    void PreordenI(NodoProducto *R);
    void cambiarStock(NodoProducto* &_raiz,int _codProducto, int _cantidad);
    void getNodoProducto(int _codProducto, NodoProducto* _raiz,NodoProducto* &_nuevoNodo);

    void getProductoMasVendido( NodoProducto* _raiz,NodoProducto* &_nuevoNodo);
    void getProductosCambiaronStock(NodoProducto* _raiz, std::string &_string);



    //PRUEBAS
    NodoProducto* torsion(NodoProducto* T);
    NodoProducto* division(NodoProducto*T);
    NodoProducto* insertar(NodoProducto* T,int _codigoProducto, int _codigoCategoria, std::string _nombreProducto, double _precioPorUnidad, int _cantidadEnStock);
    NodoProducto* borrar(NodoProducto* T, int _codPro);



};

#endif // ARBOLPRODUCTOS_H
