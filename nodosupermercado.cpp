#include "nodosupermercado.h"


void NodoSupermercado::insertarNodo(int _codSuper, int _codLugar, std::string _nombre) {

    if(_codSuper<codSuper){
        if(Hizq==NULL){
            Hizq = new NodoSupermercado(_codSuper, _codLugar,_nombre);
        }else{
            Hizq->insertarNodo(_codSuper, _codLugar,_nombre);
        }
    }if(_codSuper>codSuper){
        if(Hder==NULL){
            Hder = new NodoSupermercado(_codSuper, _codLugar,_nombre);
            Hder->insertarNodo(_codSuper, _codLugar,_nombre);
        }
    }

}

int NodoSupermercado::obtenerValor() {
    return codSuper;
}
