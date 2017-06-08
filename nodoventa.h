#ifndef NODOVENTA_H
#define NODOVENTA_H
//#include <stdio.h>
//#include <stdlib.h>
#include <string>


class NodoVenta {
public:
    NodoVenta(int _codProv, std::string _nombreProv, int _codClient, std::string _nombreClient, int _codCat, std::string _descCat,
              int _codProdu, std::string _nombreProdud, double _precioxuni, int cant, double _monto){
        codigoProv = _codProv;
        nombreProv = _nombreProv;
        codigoCliente = _codClient;
        nombreCliente = _nombreClient;
        codCategoria = _codCat;
        descCategoria = _descCat;
        codProd = _codProdu;
        nombreProducto = _nombreProdud;
        cantidadComprada = cant;
        precioPorUnidad = _precioxuni;
        monto = _monto;
        siguiente = NULL;
        anterior = NULL;

    }

    std::string toString();

    int getCodClient(){ return codigoCliente;};
    int getCodProv(){ return codigoProv;};
    int getCant(){return cantidadComprada;};
    int getCodCat(){return codCategoria;}
    int getCodProd(){return codProd;}

    double getPrecioPorUnidad(){return precioPorUnidad;}
    std::string getNomProd(){ return nombreProducto;}
    std::string getDescCat(){return descCategoria;}
    std::string getNomClient() {return nombreCliente;};
    std::string getNomProv() {return nombreProv;};
    double getMontoTotal() {return monto;};

    NodoVenta* anterior;
    NodoVenta* siguiente;
private:
    int codigoProv;
    std::string nombreProv;
    int codigoCliente;
    std::string nombreCliente;
    int cantidadComprada;
    int codCategoria;
    std::string descCategoria;
    int codProd;
    std::string nombreProducto;
    double precioPorUnidad;
    double monto;


    friend class ListaVentas;

};

#endif // NODOVENTA_H
