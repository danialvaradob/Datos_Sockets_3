#include "nodoventa.h"
#include <sstream>

std::string NodoVenta::toString() {
    std::stringstream flujo;
    std::stringstream flujo1;
    std::stringstream flujo2;
    std::stringstream flujo3;
    std::stringstream flujo4;
    std::stringstream flujo5;
    std::stringstream flujo6;
    std::string _codProv;
    std::string _codCliente;
    std::string _cant;
    std::string _monto;
    std::string _codProd;
    std::string _codCat;
    std::string _precioXunidad;

    flujo << codigoProv;
    _codProv = flujo.str();
    flujo2 << codigoCliente;
    _codCliente = flujo2.str();
    flujo1 << cantidadComprada;
    _cant = flujo1.str();
    flujo3 << monto;
    _monto = flujo3.str();
    flujo4 << codProd;
    _codProd = flujo4.str();
    flujo5 << codCategoria;
    _codCat = flujo5.str();
    flujo6 << precioPorUnidad;
    _precioXunidad = flujo6.str();


    return "Nombre del proveedor: "+nombreProv+
            "\nCodigo del proveedor: "+_codProv+
            "\nNombre del cliente: "+nombreCliente+
            "\nCodigo del cliente: "+_codCliente+
            "\nDescripcion de la categoria: "+descCategoria+
            "\nCodigo de la categoria: "+_codCat+
            "\nNombre del producto: "+nombreProducto+
            "\nCodigo del producto: "+_codProd+
            "\nPrecio por unidad: "+_precioXunidad+
            "\nCantidad comprada del producto: "+_cant+
            "\nMonto a pagar: "+_monto;
}

