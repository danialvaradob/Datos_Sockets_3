#ifndef NODOPRODUCTO_H
#define NODOPRODUCTO_H
#include <string>
#include <iostream>




class NodoProducto {
public:
    NodoProducto() {
        codigoProducto = 0;
        codigoCategoria = 0;
        nombreProducto = "";
        precioPorUnidad = 0;
        cantidadEnStock = 0;
        cantidadAlInicio = 0;
        cont = 0;
        nivel = 0;
        cantidadProductoVendido = 0;
        bestScore = 0;
        padre = NULL;
        raiz = NULL;
        izq = NULL;
        der = NULL;
    }

    NodoProducto(int _codigoProducto, int _codigoCategoria, std::string _nombreProducto, double _precioPorUnidad, int _cantidadEnStock){

        codigoProducto = _codigoProducto;
        codigoCategoria = _codigoCategoria;
        nombreProducto = _nombreProducto;
        precioPorUnidad = _precioPorUnidad;
        cantidadEnStock = _cantidadEnStock;
        cantidadAlInicio = _cantidadEnStock;


        cont = 0;
        nivel = 0;
        cantidadProductoVendido = 0;
        bestScore = 0;

        padre = NULL;
        raiz = NULL;
        izq = NULL;
        der = NULL;

    }

    NodoProducto *getSiguiente();
    void setSiguiente(NodoProducto* _siguiente);
    NodoProducto *getAnterior();
    void setAnterior(NodoProducto* _anterior);
    NodoProducto *getPrimerProducto();
    void setPrimeroProducto( NodoProducto* _primerProducto);

    int getCodigoProducto();
    int getCodigoCategoria();
    std::string getNombreProducto();
    double getPrecioPorUnidad();
    int getCantidadEnStock();
    void setCantidadEnStock(int _cantidadNueva);
    int getCantidadAlInicio() { return cantidadAlInicio;}
    void aumentarCantidadProductosVendidos() {cantidadProductoVendido++;}
    int getCantidadProVend() {return cantidadProductoVendido;}
    bool cantSuficiente(int cant_a_comprar){return (cantidadEnStock - cant_a_comprar) >= 0;};
    void setBestScore(int v);
    bool cambioEnStock(){return (cantidadEnStock != cantidadAlInicio);};
    double calcularMonto(int cant, int descuento);
    int getBestScore() {return bestScore;}

    void setCodigo(int _codPro) {codigoProducto = _codPro;}

    // especiales para Nodos de un arbol AA
    NodoProducto* izq;
    NodoProducto* der;
    NodoProducto* padre;
    NodoProducto* raiz;

    int cont;
    int nivel;


private:
    int cantidadProductoVendido;
    int codigoProducto;
    int codigoCategoria;
    std::string nombreProducto;
    double precioPorUnidad;
    int cantidadEnStock;
    int cantidadAlInicio;
    int bestScore;

    NodoProducto *siguiente;
    NodoProducto *anterior;

    friend class NodoCategoria;


};


#endif // NODOPRODUCTO_H
