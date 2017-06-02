//
// Created by Daniel Alvarado on 5/18/17.
//

#ifndef PROGRA_3_NODOLUGAR_H
#define PROGRA_3_NODOLUGAR_H

#include <string>
#include "listaconexiones.h"

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

    }

    NodoLugar(int _codigo, std::string _nombre) {
        codigo = _codigo;
        nombre = _nombre;
        cantidadSupermercados = 0;

        siguiente = NULL;
        anterior = NULL;
        ListaConexiones* listaConexiones = new ListaConexiones();
        conexiones = listaConexiones;
        visitado = false;


    }

    int getCodigo() {return codigo;}
    std::string getNombre() {return nombre;}
    NodoLugar* getAnteior() {return anterior;}
    NodoLugar* getSiguiente() {return siguiente;}
    int getCantidad() {return cantidadSupermercados;}
    void aumentarCantidadSuper() {cantidadSupermercados++;}


    //Conexiones
    ListaConexiones* getConexiones() {return conexiones;}
    int getCantidadDeConexiones() {return conexiones->largoLista();}
    int getCodigoMenorConexion(){return conexiones->getCodMenorConexion();};
    int getPesoMenorConexion(int _codigo){return conexiones->getPeso(_codigo); }
    void visitar() {visitado = true;};

    void visitarConexion(int _codigo) {conexiones->visitar(_codigo);}
    void desvisitarConexiones() {conexiones->desvisitarConexiones();}

private:
    bool visitado;
    int codigo;
    std::string nombre;
    int cantidadSupermercados;
    NodoLugar* siguiente;
    NodoLugar* anterior;

    ListaConexiones* conexiones;



    friend class ListaLugares;
    friend class ArbolExpansionMinimo;

};

#endif //PROGRA_3_NODOLUGAR_H
