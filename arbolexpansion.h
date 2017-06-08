//
// Created by Daniel Alvarado on 5/20/17.
//

#ifndef PROGRA_3_ARBOLEXPANSION_H
#define PROGRA_3_ARBOLEXPANSION_H\


#include "nodoarbolexpansion.h"
#include "listaconjunto.h"

class ArbolExpansionMinimo {

public:

    bool arbolVacio() {return primero == NULL;}
    int largoArbol();
    //constructor
    //ArbolExpansionMinimo(ListaLugares* _grafo);

    ArbolExpansionMinimo() {
        primero = NULL;
        n = 0;
        pesoTotal = 0;
    }

    //int **OT() {return T;} //Arbol de Expansion
    //int arbolExpancionPrim(ListaLugares* _grafo);    //algoritmo de Prim
    std::string prim(ListaLugares* _grafo, int _primerNodo);
    std::string getPrim();



    void profundida(ListaLugares* _grafo, int _puntoInicial);
    void kruskal(ListaLugares* _grafo, int _primerNodo);

    NodoArbolExpansion *obetenerNodoEnPosicion(int pos);
    void ordenarKruskal();
    void seleccionarAristas(ListaConjunto *conjunto);
    std::string imprimirKruskal();


    void insertarNodo(int _codigo1, int _codigo2 , int _peso);
    bool existeConexion(int _codigo1, int _codigo2);
    int getPesoTotal(){return pesoTotal;}
    bool nodoVisitado(int _codigo);


    int n;
private:
    int pesoTotal;


    NodoArbolExpansion* primero;
};


#endif //PROGRA_3_ARBOLEXPANSION_H
