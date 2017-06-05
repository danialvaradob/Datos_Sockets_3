#ifndef ARBOLCLIENTES_H
#define ARBOLCLIENTES_H
#include <iostream>
//#include <string>
#include "nodocliente.h"

//ARBOL B


class ArregloClaves
{
public:

    ArregloClaves(){

        for(int clave = 0; clave < 5; clave++){
            arregloClaves[clave] = NULL;
        }
    }

    void InsertarClave(pNodoCliente Clave, int Numero);
    int ObtenerClave(int Numero);
    pNodoCliente ObtenerApuntadorClave(int Numero);


    pNodoCliente arregloClaves[5];
private:

    friend class Pagina;
};


typedef ArregloClaves *ApuntadorClaves;

class Pagina;
typedef Pagina *ApuntadorPagina;

class ArregloRamas
{
public:

    ArregloRamas(){
        for(int k = 0; k < 5; k++){
            arregloRamas[k] = NULL;
        }
    }
    void InsertarRama(ApuntadorPagina Rama, int Numero);
    ApuntadorPagina ObtenerRama(int Numero);

    ApuntadorPagina arregloRamas[5];
private:

    friend class Pagina;
};

typedef ArregloRamas *ApuntadorRamas;


class Pagina
{
public:
    Pagina(){
        cuenta = 0;
        Claves = new ArregloClaves();
        Ramas = new ArregloRamas();
        EmpujarArriba = false;
        X = 0;
        Xr = NULL;
        K = 0;
        Esta = false;
        llamadas = 0;
    }

    int cuenta;
    ApuntadorClaves Claves;
    ApuntadorRamas Ramas;
    bool EmpujarArriba;
    int X;
    ApuntadorPagina Xr;
    int K;
    bool Esta;
    int llamadas;

    friend class ArbolClientes;

};

class ArbolClientes
{
public:

    ArbolClientes(){
        raizB = NULL;
    }
    bool BVacio(){return raizB == NULL;}
    void EstablecerRaizB(ApuntadorPagina Raiz);
    void IniciarInsercionB(int Numero, int _id, std::string _nombre, std::string _direccion, int _telefono);
    ApuntadorPagina InsertarB(ApuntadorPagina Raiz, int Numero,  int _id, std::string _nombre, std::string _direccion, int _telefono);
    ApuntadorPagina EmpujarB(ApuntadorPagina Raiz, int Numero, int _id, std::string _nombre, std::string _direccion, int _telefono);
    ApuntadorPagina BuscarNodoB(ApuntadorPagina Raiz, int Numero);
    ApuntadorPagina MeterHojaB(ApuntadorPagina Raiz, int _id, std::string _nombre, std::string _direccion, int _telefono);
    ApuntadorPagina DividirNodoB(ApuntadorPagina Raiz,  int _id, std::string _nombre, std::string _direccion, int _telefono);
    void IniciarRecorridoB();
    void RecorridoInordenB(ApuntadorPagina Raiz);
    void existeCliente(ApuntadorPagina Raiz,int _Numero,bool& _existe);
    void PreordenSocket(ApuntadorPagina _raiz, std::string &_string);
    void getClienteMasCompras(ApuntadorPagina Raiz,NodoCliente*& _clienteMasCompras);
    void agregarCompra(ApuntadorPagina Raiz,int _codCliente);
    void getCliente(ApuntadorPagina Raiz,NodoCliente*& _clienteMasCompras, int _id);
    void Combina(ApuntadorPagina P, int& K);
    void MoverIzquierda (ApuntadorPagina P, int& K);
    void MoverDerecha(ApuntadorPagina P, int& K);
    void Restablecer (ApuntadorPagina P, int& K);
    void Sucesor(ApuntadorPagina P, int& K);
    void Quitar(ApuntadorPagina & P, int& K);
    void EliminarRegistro(int C1, ApuntadorPagina Raiz, bool & Encontrado);
    void Eliminar (int C1, ApuntadorPagina Raiz);
    void BuscarNodo(int Clave, ApuntadorPagina P, bool & Encontrado, int & K);


    // Funcion que simplemente agrega un cliente usando IniciarInsercionB(para Numero se utiliza el mismo _id, son 2 _id
    // en total)
    void Clientes();


    //private:

    ApuntadorPagina raizB;

};


//-----------Pila-----------//
/*
class PilaB {
public:
    PilaB() : plistaB(NULL) {}

    void Push(pNodoCliente);

    bool Vacia() { return plistaB == NULL; }
    pNodoCliente Pop();
    int Size();

    pNodoCliente plistaB;
};

void PilaB::Push(pNodoCliente v)
{
    if(Vacia()) {
        plistaB = v;
    }else{
        NodoCliente *aux = plistaB;
        while(aux->siguiente){
            aux = aux->siguiente;
        }
        aux->siguiente = v;
        v->anterior = aux;

    }
}

pNodoCliente PilaB::Pop()
{
    NodoCliente *borrar = NULL;
    NodoCliente *salida = NULL;
    if(Vacia()){
        cout<<"Pila Vacia"<<endl;
    }else{
        borrar = plistaB;
        while(borrar->siguiente){
            borrar=borrar->siguiente;
        }
        if(Size()>1){
            salida = borrar;
            borrar->anterior->siguiente=NULL;
            borrar = NULL;
            delete borrar;
        }else{
            salida = plistaB;
            plistaB = NULL;
        }
    }
    return salida;
}
*/
/*
int PilaB::Size(){
    while(plistaB && plistaB->anterior) plistaB = plistaB->anterior;
    int cont=0;
    NodoCliente *aux;
    aux = plistaB;
    while(aux){
        cont++;
        aux = aux->siguiente;
    }
    return cont;
}

void Arbol::Clientes(){
    fstream ficheroEntrada;
    string frase;
    string caracter;
    string palabra;
    int idCliente;
    string nombre;
    string telefono;
    string apellido;
    string ciudad;
    int cont=1;

    ficheroEntrada.open("C:/Users/carlo/Desktop/Proyectos y Tareas C++/Proyecto_3/Clientes.txt" , ios::in);
    if (ficheroEntrada.is_open()) {
        while (! ficheroEntrada.eof() ) {
            getline (ficheroEntrada,frase);
            int largo=frase.size();
            for (int i=0;i<=largo;i++){
                caracter=frase[i];
                if (caracter!=";"){
                    palabra+=caracter;
                }
                else{
                    switch(cont){
                        case 1:
                            idCliente=transformar(palabra);
                        case 2:
                            nombre=palabra;
                            break;
                        case 3:
                            apellido=palabra;
                            break;
                        case 4:
                            ciudad=palabra;
                            break;
                    }
                    cont++;
                    palabra="";
                }
            }
            cont=1;
            telefono=palabra;
            palabra="";
            IniciarInsercionB(idCliente,idCliente,nombre,apellido, ciudad, telefono);
        }
        ficheroEntrada.close();
    }
}
 */

#endif // ARBOLCLIENTES_H
