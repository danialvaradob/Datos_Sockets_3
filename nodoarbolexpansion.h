//
// Created by Daniel Alvarado on 5/29/17.
//

#ifndef PROGRA_3_NODOARBOLEXPANSION_H
#define PROGRA_3_NODOARBOLEXPANSION_H


#include "nodoconexion.h"

class NodoArbolExpansion{

public:
    NodoArbolExpansion(int _codigo1, int _codigo2, int _peso) {
        codLugar1 = _codigo1;
        codLugar2 = _codigo2;
        peso = _peso;
        ordenado = false;
        kruskalElegido = false;

    }
    std::string toString();

private:
    int codLugar1;
    int codLugar2;
    int peso;
    bool ordenado;
    bool kruskalElegido;

    NodoArbolExpansion* anterior;
    NodoArbolExpansion* siguiente;
    friend class ArbolExpansionMinimo;



};


#endif //PROGRA_3_NODOARBOLEXPANSION_H
