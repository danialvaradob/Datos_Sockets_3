#include <fstream>
#include "listaventas.h"

void ListaVentas::insertar(NodoVenta *v)
{
    if (listaVacia())
    {
        primero = v;
        primero->anterior=primero;
        primero->siguiente=primero;
    }
    else
    {
        NodoVenta *nuevo = v;
        nuevo->anterior = primero->anterior;
        nuevo->siguiente=primero->anterior->siguiente;
        primero->anterior->siguiente=nuevo;
        primero->anterior=nuevo;
    }
}

void ListaVentas::crearFactura() {
    std::ofstream escritura("Factura.txt");
    NodoVenta *_nodo = primero;
    escritura << "VENTA-------------------------------------------" << std::endl;
    escritura << "Nombre del proveedor: " << _nodo->getNomProv() << std::endl;
    escritura << "ID del proveedor: " << _nodo->getCodProv() << std::endl;
    escritura << "Nombre del cliente: " << _nodo->getNomClient() << std::endl;
    escritura << "ID del cliente: " << _nodo->getCodClient() << std::endl;
    escritura << "Descripcion de la categoria: " << _nodo->getDescCat() << std::endl;
    escritura << "Codigo de la categoria: " << _nodo->getCodCat() << std::endl;
    escritura << "Nombre del producto: " << _nodo->getNomProd() << std::endl;
    escritura << "Codigo del producto: " << _nodo->getCodProd() << std::endl;
    escritura << "Cantidad solicitada: " << _nodo->getCant() << std::endl;
    escritura << "Precio por unidad: " << _nodo->getPrecioPorUnidad() << std::endl;
    escritura << "Monto: " << _nodo->getMontoTotal() << std::endl;
    _nodo = _nodo->siguiente;

    while(_nodo != primero){
        escritura << "VENTA-------------------------------------------" << std::endl;
        escritura << "Nombre del proveedor: " << _nodo->getNomProv() << std::endl;
        escritura << "ID del proveedor: " << _nodo->getCodProv() << std::endl;
        escritura << "Nombre del cliente: " << _nodo->getNomClient() << std::endl;
        escritura << "ID del cliente: " << _nodo->getCodClient() << std::endl;
        escritura << "Descripcion de la categoria: " << _nodo->getDescCat() << std::endl;
        escritura << "Codigo de la categoria: " << _nodo->getCodCat() << std::endl;
        escritura << "Nombre del producto: " << _nodo->getNomProd() << std::endl;
        escritura << "Codigo del producto: " << _nodo->getCodProd() << std::endl;
        escritura << "Cantidad solicitada: " << _nodo->getCant() << std::endl;
        escritura << "Precio por unidad: " << _nodo->getPrecioPorUnidad() << std::endl;
        escritura << "Monto: " << _nodo->getMontoTotal() << std::endl;
        _nodo = _nodo->siguiente;
    }
    escritura.close();
}
