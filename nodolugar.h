//
// Created by Daniel Alvarado on 5/18/17.
//

#ifndef PROGRA_3_NODOLUGAR_H
#define PROGRA_3_NODOLUGAR_H


#include "listaconexiones.h"
#include "arbolsupermercados.h"

class NodoLugar {
public:
    NodoLugar() {
        codigo = 0;
        nombre = " ";
        cantidadSupermercados = 0;

        siguiente = NULL;
        anterior = NULL;
        visitado = false;

        ListaConexiones* listaConexiones = new ListaConexiones();
        conexiones = listaConexiones;
        ArbolSupermercados* arbolSuper = new ArbolSupermercados();
        punteroSuper = arbolSuper;

    }

    NodoLugar(int _codigo, std::string _nombre) {
        codigo = _codigo;
        nombre = _nombre;
        cantidadSupermercados = 0;

        siguiente = NULL;
        anterior = NULL;
        ListaConexiones* listaConexiones = new ListaConexiones();
        conexiones = listaConexiones;
        ArbolSupermercados* arbolSuper = new ArbolSupermercados();
        punteroSuper = arbolSuper;
        visitado = false;


    }

    int getCodigo() {return codigo;}
    std::string getNombre() {return nombre;}
    NodoLugar* getAnteior() {return anterior;}
    NodoLugar* getSiguiente() {return siguiente;}
    int getCantidad() {return cantidadSupermercados;}
    void aumentarCantidadSuper() {cantidadSupermercados++;}
    ArbolSupermercados *getArbolSuper(){return punteroSuper;}

    //Conexiones
    ListaConexiones* getConexiones() {return conexiones;}
    int getCantidadDeConexiones() {return conexiones->largoLista();}
    int getCodigoMenorConexion(){return conexiones->getCodMenorConexion();};
    int getPesoMenorConexion(int _codigo){return conexiones->getPeso(_codigo); }
    void visitar() {visitado = true;};

    void visitarConexion(int _codigo) {conexiones->visitar(_codigo);}
    void desvisitarConexiones() {conexiones->desvisitarConexiones();}
    bool existeConexion(int _codigo) {return conexiones->existeConexion(_codigo);}

private:
    bool visitado;
    int codigo;
    std::string nombre;
    int cantidadSupermercados;
    NodoLugar* siguiente;
    NodoLugar* anterior;

    ArbolSupermercados* punteroSuper;

    ListaConexiones* conexiones;



    friend class ListaLugares;
    friend class ArbolExpansionMinimo;

};

#endif //PROGRA_3_NODOLUGAR_H
