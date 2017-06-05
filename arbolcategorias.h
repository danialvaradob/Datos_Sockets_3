#ifndef ARBOLCATEGORIAS_H
#define ARBOLCATEGORIAS_H

//#include <iostream>
#include "nodocategoria.h"
//ARBOL ROJINEGRO



class ArbolCategorias
{
public:
    ArbolCategorias(){
        raiz = NULL;
    }

    void insertarValorNodoRN (int _idCategoria, std::string _descrip);
    void inordenRN(nodocategoria *R);
    void levelOrder();

    void rotarIzquierda(nodocategoria *&, nodocategoria *&);
    void rotarDerecha(nodocategoria *&, nodocategoria *&);
    void aplicarReglas(nodocategoria *&, nodocategoria *&);
    nodocategoria* InsertarNodoRN(nodocategoria* RaizRN, nodocategoria *pt);
    bool existeCategoria(int _id, nodocategoria *_raiz);
    bool existeProducto(int _codProducto, int _codCategoria, nodocategoria* _raiz); //utilizado para buscar un producto
    void PreordenSocket(nodocategoria *_raiz, std::string &_string);
    void InordenRN(nodocategoria *T);
    nodocategoria *raiz;

    void agregarProducto(nodocategoria* _raiz,int codProI, int codCatI, std::string nombreProducto, double precioPorUnidad, int cantidadEnStock);
    void getCategoriaMasVendida(nodocategoria *_raiz, nodocategoria *&NuevoNodo);
    void getArbolProd(nodocategoria* _raiz,int codCat,ArbolProductos* &arbolProductos);
    void getNodoCat(nodocategoria*_raiz,int codCat,nodocategoria* &_nuevoNodo);


};

#endif // ARBOLCATEGORIAS_H
