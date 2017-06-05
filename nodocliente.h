#ifndef NODOCLIENTE_H
#define NODOCLIENTE_H
//#include <stdio.h>

#include <string>



class NodoCliente {
public:

    NodoCliente() {
        numero = 0;
        idx = 0;
        nombre = " ";
        direccion = " ";
        telefono = 0;
        siguiente = NULL;
        anterior = NULL;
        izq = NULL;
        der = NULL;
        cantidadDeCompras = 0;

    }

    NodoCliente(int _numero, int _id, std::string _nombre, std::string _direccion, int _telefono)
    {
        numero = _numero;
        idx = _id;
        nombre = _nombre;
        direccion = _direccion;
        telefono = _telefono;
        siguiente = NULL;
        anterior = NULL;
        izq = NULL;
        der = NULL;
        cantidadDeCompras = 0;
    }

    std::string toString();

    void setHIzq(NodoCliente *nodo);
    NodoCliente *getHIzq(){return izq;};
    void setHDer(NodoCliente *nodo);
    NodoCliente *getHDer(){return der;};
    void setSiguiente(NodoCliente *nodo);
    NodoCliente *getSiguiente(){return siguiente;};
    void setAnterior(NodoCliente *nodo);
    NodoCliente *getAnterior(){return anterior;}

    int getNumero(){return numero;};
    std::string getNombre(){return nombre;};
    std::string getDireccion(){ return direccion;};
    int getID(){ return idx;};
    int getTelefono(){ return telefono;};
    int getCantidadCompras(){ return cantidadDeCompras;};
    void aumentarVentas(){cantidadDeCompras++;}

private:
    int numero;
    int idx;
    std::string nombre;
    std::string direccion;
    int telefono;
    int cantidadDeCompras;
    NodoCliente* izq;
    NodoCliente* der;
    NodoCliente *siguiente;
    NodoCliente *anterior;

    //friend class ListaProveedores;
    friend class ArbolClientes;
    friend class Pagina;
    friend class ArregloClaves;


};

typedef NodoCliente* pNodoCliente;


#endif // NODOCLIENTE_H
