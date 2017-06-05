#ifndef NODOPROVEEDOR_H
#define NODOPROVEEDOR_H
#include <string>





class NodoProveedor {
public:

    NodoProveedor() {
            numero = 0;
            nombre = " ";
            direccion = " ";
            telefono = 0;

            siguiente = NULL;
            anterior = NULL;

            cantidadDeVentas = 0;
            Hizq=NULL;
            Hder=NULL;



    }

    NodoProveedor(int _codP, std::string _nombre, std::string _dir, int _tel){
        numero = _codP;
        nombre = _nombre;
        direccion = _dir;
        telefono = _tel;

        siguiente = NULL;
        anterior = NULL;

        cantidadDeVentas = 0;
        Hizq=NULL;
        Hder=NULL;

    }

    std::string toString();

    NodoProveedor *getSiguiente();
    void setSiguiente(NodoProveedor* _siguiente);
    NodoProveedor *getAnterior();
    void setAnterior(NodoProveedor* _anterior);

    std::string getNombre();
    std::string getDireccion();
    int getID();
    int getTelefono();
    int getCantidadDeVentas();
    void aumentarVentas(){cantidadDeVentas++;}

    // Metodo utilizado para agregar un nodo de forma correcta
    void insertarProveedor(int idProveedor,std::string nombre,std::string direccion,int intTel);

    NodoProveedor *Hizq;
    NodoProveedor *Hder;




private:
    int numero;
    std::string nombre;
    std::string direccion;
    int telefono;
    int bestScore;
    NodoProveedor *siguiente;
    NodoProveedor *anterior;

    int cantidadDeVentas;

    friend class ArbolProveedores;


};

typedef NodoProveedor* pNodoProveedor;

#endif // NODOPROVEEDOR_H
