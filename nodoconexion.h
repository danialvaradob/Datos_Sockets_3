//
// Created by Daniel Alvarado on 5/18/17.
//

#ifndef PROGRA_3_NODOCONEXION_H
#define PROGRA_3_NODOCONEXION_H

#include <string>

class NodoConexion {
public:
    NodoConexion() {
        codLugar = 0;
        peso = 0;
        visitado = false;
    }

    NodoConexion(int _codigo, int _peso) {
        codLugar = _codigo;
        peso = _peso;
        visitado = false;
    }


    int codLugar;
    int peso;
    NodoConexion* anterior;
    NodoConexion* siguiente;
    bool visitado;
    
    int codigoUltimaConexion;

private:

    friend class ListaConexiones;
    friend class NodoArbolExpansion;

};


#endif //PROGRA_3_NODOCONEXION_H
