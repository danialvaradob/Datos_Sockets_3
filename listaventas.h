#ifndef LISTAVENTAS_H
#define LISTAVENTAS_H

#include "nodoventa.h"
//#include "arbolcategorias.h"
//#include "arbolclientes.h"
//#include "arbolproductos.h"
//#include "arbolsupermercados.h"
//#include "arbolproveedores.h"
//#include <string>

class ListaVentas {
public:
    ListaVentas() {primero = NULL;}

    void insertar(NodoVenta *_venta);
    bool listaVacia() {return primero == NULL;}
    void crearFactura();

    NodoVenta* getPrimero() {return primero;};

private:
    NodoVenta* primero;

};

#endif // LISTAVENTAS_H
