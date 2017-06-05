#include "nodoproducto.h"



int NodoProducto::getCodigoProducto(){
    return codigoProducto;
}

int NodoProducto::getCodigoCategoria(){
    return codigoCategoria;
}

std::string NodoProducto::getNombreProducto(){
    return nombreProducto;
}

double NodoProducto::getPrecioPorUnidad(){
    return precioPorUnidad;
}

int NodoProducto::getCantidadEnStock(){
    return cantidadEnStock;
}

NodoProducto* NodoProducto::getAnterior(){
    return anterior;
}
NodoProducto* NodoProducto::getSiguiente(){
    return siguiente;
}

void NodoProducto::setAnterior(NodoProducto* _anterior){
    anterior = _anterior;
}


void NodoProducto::setSiguiente(NodoProducto* _siguiente){
    anterior = _siguiente;
}

void NodoProducto::setCantidadEnStock(int comprado) {
    if (cantSuficiente(comprado)) {
        cantidadEnStock = cantidadEnStock - comprado;
        setBestScore(comprado);
    }
}

void NodoProducto::setBestScore(int v){
    bestScore = bestScore + v;
}

double NodoProducto::calcularMonto(int cant, int descuento){
    double monto = cant * precioPorUnidad;
    if(descuento == 0)
        return monto;
    else{
        double _montoAdescontar = monto * 0.05;
        monto = monto - _montoAdescontar;
        return monto;
    }
}

